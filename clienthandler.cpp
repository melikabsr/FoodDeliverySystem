#include "clienthandler.h"
#include "userdatabase.h"
#include "restaurantdata.h"
#include <QTextStream>
#include <QDebug>
#include <QtCompare>
#include "ServerOrder.h"
#include "OrderManager.h"

//#include "order.h"
#include "ordermanager.h"

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
    }else if (command == "GET_ORDERS") {
        handleGetOrders(parts);
    }else {
        socket->write("❓ Unknown command\n");
    }
}

void ClientHandler::handleLogin(const QStringList& parts)
{
    if (parts.size() < 3) {
        socket->write("❌ LOGIN|Missing fields\n");
        return;
    }

    QString u = parts[1];
    QString p = parts[2];

    if (UserDatabase::instance().validateLogin(u, p)) {
        username = u;
        socket->write("✅ LOGIN|SUCCESS\n");
    } else {
        socket->write("❌ LOGIN|FAILED\n");
    }
}

void ClientHandler::handleGetRestaurants()
{
    QString data = RestaurantData::instance().serializeRestaurants();
    socket->write(("RESTAURANTS|" + data + "\n").toUtf8());
}

void ClientHandler::handleGetMenu(const QStringList& parts)
{
    if (parts.size() < 2) {
        socket->write("❌ GET_MENU|Missing ID\n");
        return;
    }

    bool ok;
    int id = parts[1].toInt(&ok);
    if (!ok) {
        socket->write("❌ GET_MENU|Invalid ID\n");
        return;
    }

    const Restaurant* r = RestaurantData::instance().getRestaurantById(id);
    if (!r) {
        socket->write("❌ GET_MENU|Not Found\n");
        return;
    }

    socket->write(("MENU|" + r->serializeMenu() + "\n").toUtf8());
}




void ClientHandler::handleAddOrder(const QStringList& parts)
{
    if (parts.size() < 4) {
        socket->write("❌ ADD_ORDER|Missing fields\n");
        return;
    }

    QString user = parts[1];
    bool ok;
    int restId = parts[2].toInt(&ok);
    if (!ok) {
        socket->write("❌ ADD_ORDER|Invalid restaurant ID\n");
        return;
    }

    QString itemsStr = parts[3];
    QStringList itemTokens = itemsStr.split(",");
    if (itemTokens.isEmpty()) {
        socket->write("❌ ADD_ORDER|No items\n");
        return;
    }

    const Restaurant* r = RestaurantData::instance().getRestaurantById(restId);
    if (!r) {
        socket->write("❌ ADD_ORDER|Restaurant not found\n");
        return;
    }

    ServerOrder newOrder(OrderManager::instance().generateNewId(), user);

    const QList<Food>& menu = r->getMenu();
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

    OrderManager::instance().addOrder(newOrder);
    socket->write("✅ ADD_ORDER|Order registered\n");
}

void ClientHandler::handleGetOrders(const QStringList& parts)
{
    if (parts.size() < 2) {
        socket->write("❌ GET_ORDERS|Missing username\n");
        return;
    }

    QString username = parts[1];
    const QVector<ServerOrder> userOrders = OrderManager::instance().getOrdersForCustomer(username);

    if (userOrders.isEmpty()) {
        socket->write("ORDERS|No orders found\n");
        return;
    }

    QStringList serialized;
    for (const ServerOrder& order : userOrders) {
        QStringList itemsStr;
        for (const auto& pair : order.getItems()) {
            const Food& food = pair.first;
            int qty = pair.second;
            itemsStr << QString("%1×%2").arg(food.getName()).arg(qty);
        }

        QString info = QString("🧾 Order #%1 - Total: %2 تومان - [%3]")
                           .arg(order.getId())
                           .arg(order.getTotalAmount())
                           .arg(itemsStr.join(", "));
        serialized << info;
    }

    QString final = "ORDERS|" + serialized.join(";");
    socket->write((final + "\n").toUtf8());
}
