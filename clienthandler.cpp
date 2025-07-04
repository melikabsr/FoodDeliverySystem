#include "clienthandler.h"
#include "DatabaseManager.h"
#include <QTextStream>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "ServerOrder.h"
#include "OrderManager.h"
#include "Food.h"
#include "OrderPersistence.h"
ClientHandler::ClientHandler(QTcpSocket* socket, QObject* parent)
    : QThread(parent), socket(socket)
{}

void ClientHandler::run()
{
    if (!socket->waitForReadyRead(3000)) {
        socket->close();
        return;
    }

    while (socket->state() == QTcpSocket::ConnectedState) {
        if (!socket->waitForReadyRead(5000)) continue;

        QString msg = QString::fromUtf8(socket->readAll()).trimmed();
        qDebug() << "📨 From client:" << msg;
        processMessage(msg);
    }

    socket->close();
}

void ClientHandler::processMessage(const QString& msg)
{
    QStringList parts = msg.split("|");
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    if (command == "LOGIN") {
        handleLogin(parts);
    } else if (command == "GET_RESTAURANTS") {
        handleGetRestaurants();
    } else if (command == "GET_MENU") {
        handleGetMenu(parts);
    } else if (command == "ADD_ORDER") {
        handleAddOrder(parts);
    } else if (command == "GET_ORDERS") {
        handleGetOrders(parts);
    } else if (command == "UPDATE_ORDER_STATUS") {
        handleUpdateOrderStatus(parts);
    } else {
        socket->write("❓ Unknown command\n");
    }
}
void ClientHandler::handleLogin(const QStringList& parts)
{
    if (parts.size() < 4) {
        socket->write("LOGIN_RESULT|FAILED|MISSING_FIELDS\n");
        return;
    }

    QString u = parts[1].trimmed();
    QString p = parts[2].trimmed();
    QString role = parts[3].trimmed().toUpper();

    qDebug() << "🧪 Login request:" << u << p << role;

    // ADMIN → بررسی خاص
    if (role == "ADMIN") {
        if (u == "admin" && p == "admin") {
            username = u;
            socket->write("LOGIN_RESULT|SUCCESS|ADMIN\n");
        } else {
            socket->write("LOGIN_RESULT|FAILED|NOT_ADMIN\n");
        }
        return;
    }

    QSqlDatabase db = DatabaseManager::instance().getDatabase();

    // بررسی وجود کاربر
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ? AND role = ?");
    query.addBindValue(u);
    query.addBindValue(p);
    query.addBindValue(role);

    bool userExists = false;
    if (query.exec() && query.next()) {
        userExists = true;
        username = u;
    }

    // ثبت کاربر جدید در صورت نیاز
    if (!userExists) {
        QSqlQuery insert(db);
        insert.prepare("INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
        insert.addBindValue(u);
        insert.addBindValue(p);
        insert.addBindValue(role);
        if (!insert.exec()) {
            qDebug() << "❌ Failed to insert user:" << insert.lastError().text();
            socket->write("LOGIN_RESULT|FAILED|DB_ERROR\n");
            return;
        }
        username = u;

        // اگر نقش owner بود → ثبت رستوران جدید
        if (role == "RESTAURANT_OWNER") {
            QSqlQuery restInsert(db);
            QString defaultRestaurantName = u + "'s Restaurant";

            restInsert.prepare("INSERT INTO restaurants (name, owner_username) VALUES (?, ?)");
            restInsert.addBindValue(defaultRestaurantName);
            restInsert.addBindValue(u);

            if (!restInsert.exec()) {
                qDebug() << "❌ Failed to insert restaurant:" << restInsert.lastError().text();
                socket->write("LOGIN_RESULT|FAILED|DB_ERROR\n");
                return;
            }
        }
    }

    if (role == "RESTAURANT_OWNER") {
        socket->write("LOGIN_RESULT|SUCCESS|RESTAURANT_OWNER\n");
    } else {
        QSqlQuery getRestIdQuery(db);
        getRestIdQuery.prepare("SELECT id FROM restaurants WHERE owner_username = ?");
        getRestIdQuery.addBindValue(u);
        if (getRestIdQuery.exec() && getRestIdQuery.next()) {
            int restId = getRestIdQuery.value(0).toInt();
            socket->write(QString("LOGIN_RESULT|SUCCESS|RESTAURANT_OWNER|%1\n").arg(restId).toUtf8());
        } else {
            qDebug() << "❌ Failed to fetch restaurant ID after insert.";
            socket->write("LOGIN_RESULT|FAILED|FETCH_RESTAURANT_ID\n");
        }


    }
}



void ClientHandler::handleGetRestaurants()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT name FROM restaurants");
    if (!query.exec()) {
        socket->write("❌ GET_RESTAURANTS|DB_ERROR\n");
        return;
    }

    QStringList items;
    while (query.next()) {
        QString name = query.value(0).toString();
        items << name;
    }

    socket->write(("RESTAURANTS|" + items.join(";") + "\n").toUtf8());
}

void ClientHandler::handleGetMenu(const QStringList& parts)
{
    if (parts.size() < 2) {
        socket->write("ERROR|GET_MENU|Missing restaurant name\n");
        return;
    }

    QString restaurantName = parts[1].trimmed();

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT id, name, description, price FROM foods WHERE restaurant_name = ?");
    query.addBindValue(restaurantName);

    if (!query.exec()) {
        socket->write("ERROR|GET_MENU|Query failed\n");
        return;
    }

    QStringList serializedMenu;
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString desc = query.value(2).toString();
        double price = query.value(3).toDouble();

        serializedMenu << QString("%1~%2~%3~%4").arg(id).arg(name).arg(desc).arg(price);
    }

    QString menuMessage = "MENU|" + serializedMenu.join(";");
    socket->write((menuMessage + "\n").toUtf8());
}
void ClientHandler::handleAddOrder(const QStringList& parts)
{
    if (parts.size() < 4) {
        socket->write("❌ ADD_ORDER|Missing fields\n");
        return;
    }

    QString user = parts[1].trimmed();
    QString restaurantName = parts[2].trimmed();
    QStringList itemTokens = parts[3].split(",");

    if (restaurantName.isEmpty() || itemTokens.isEmpty()) {
        socket->write("❌ ADD_ORDER|Invalid data\n");
        return;
    }

    // ساخت سفارش جدید
    int newId = OrderManager::instance().generateNewId();
    ServerOrder newOrder(newId, user);

    // دریافت منو
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT name, description, price FROM foods WHERE restaurant_name = ?");
    query.addBindValue(restaurantName);
    if (!query.exec()) {
        socket->write("❌ ADD_ORDER|DB_ERROR\n");
        return;
    }

    QList<Food> menu;
    while (query.next()) {
        QString name = query.value(0).toString();
        QString desc = query.value(1).toString();
        double price = query.value(2).toDouble();
        menu.append(Food(0, name, desc, price, FoodCategory::FAST_FOOD, ""));
    }

    // افزودن آیتم‌ها
    for (const QString& token : itemTokens) {
        QStringList pair = token.split(":");
        if (pair.size() != 2) continue;

        QString foodName = pair[0];
        int qty = pair[1].toInt();

        for (const Food& f : menu) {
            if (f.getName() == foodName) {
                newOrder.addItem(f, qty);
                break;
            }
        }
    }

    // ذخیره در حافظه + دیتابیس
    OrderManager::instance().addOrder(newOrder); // ← خودش ذخیره به DB رو هم انجام می‌ده

    socket->write("✅ ADD_ORDER|Order registered\n");
}

void ClientHandler::handleGetOrders(const QStringList& parts)
{
    if (parts.size() < 2) {
        socket->write("❌ GET_ORDERS|Missing username\n");
        return;
    }

    QString username = parts[1].trimmed();
    QVector<ServerOrder> orders = OrderPersistence::loadOrdersForCustomer(username);

    if (orders.isEmpty()) {
        socket->write("ORDERS|No orders found\n");
        return;
    }

    QStringList responseLines;
    for (const ServerOrder& order : orders) {
        QStringList itemStrs;
        for (const auto& pair : order.getItems()) {
            itemStrs << QString("%1×%2").arg(pair.first.getName()).arg(pair.second);
        }

        responseLines << QString("🧾 Order #%1 - %2 - Total: %3 - [%4]")
                             .arg(order.getId())
                             .arg(order.getTimestamp().toString("yyyy-MM-dd hh:mm"))
                             .arg(order.getTotalAmount())
                             .arg(itemStrs.join(", "));
    }

    socket->write(("ORDERS|" + responseLines.join(";") + "\n").toUtf8());
}

void ClientHandler::handleUpdateOrderStatus(const QStringList& parts)
{
    if (parts.size() < 3) {
        socket->write("❌ UPDATE_ORDER_STATUS|Missing fields\n");
        return;
    }

    int orderId = parts[1].toInt();
    QString statusStr = parts[2].toUpper().trimmed();

    OrderStatus status;
    if (statusStr == "PENDING") status = OrderStatus::PENDING;
    else if (statusStr == "PREPARING") status = OrderStatus::PREPARING;
    else if (statusStr == "READY") status = OrderStatus::READY;
    else if (statusStr == "DELIVERED") status = OrderStatus::DELIVERED;
    else if (statusStr == "CANCELLED") status = OrderStatus::CANCELLED;
    else {
        socket->write("❌ UPDATE_ORDER_STATUS|Invalid status\n");
        return;
    }

    ServerOrder* order = OrderManager::instance().getOrderById(orderId);
    if (!order) {
        socket->write("❌ UPDATE_ORDER_STATUS|Order not found\n");
        return;
    }

    order->setStatus(status);
    socket->write("✅ UPDATE_ORDER_STATUS|Updated successfully\n");
}
