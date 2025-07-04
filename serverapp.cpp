#include "ServerApp.h"
#include "RestaurantData.h"
#include "Food.h"
#include <QDebug>

ServerApp::ServerApp(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &ServerApp::onNewConnection);
}

bool ServerApp::startServer(quint16 port)
{
    return server->listen(QHostAddress::Any, port);
}

void ServerApp::onNewConnection()
{
    QTcpSocket* client = server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &ServerApp::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ServerApp::onClientDisconnected);
    qDebug() << "🔌 New client connected:" << client->peerAddress().toString();
}

void ServerApp::onClientDisconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    clientUsernames.remove(client);
    client->deleteLater();
    qDebug() << "🔌 Client disconnected.";
}

void ServerApp::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    while (client->canReadLine()) {
        QString message = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "📩 Received:" << message;
        handleMessage(client, message);
    }
}

void ServerApp::handleMessage(QTcpSocket* client, const QString& message)
{
    QStringList parts = message.split("|");
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    if (command == "LOGIN") handleLogin(client, parts);
    else if (command == "GET_RESTAURANTS") handleGetRestaurants(client);
    else if (command == "ADD_ORDER") handleAddOrder(client, parts);
    else if (command == "GET_MENU") handleGetMenu(client, parts);
    else if (command == "ADD_FOOD") handleAddFood(client, parts);
    else if (command == "GET_MY_MENU") handleGetMyMenu(client);
    else if (command == "REMOVE_FOOD") handleRemoveFood(client, parts);
    else client->write("❓ Unknown command\n");
}

void ServerApp::handleLogin(QTcpSocket* client, const QStringList& parts)
{
    if (parts.size() < 4) {
        client->write("LOGIN_RESULT|FAILED|INVALID_FORMAT\n");
        return;
    }

    QString username = parts[1].trimmed();
    QString password = parts[2].trimmed();
    QString rawRole = parts[3].trimmed().toLower();

    auto userOpt = userRepo.getUser(username, rawRole);

    if (userOpt.has_value()) {
        const UserData& user = userOpt.value();

        if (user.password != password) {
            client->write("LOGIN_RESULT|FAILED|WRONG_PASSWORD\n");
            return;
        }

        if (user.role.toLower() != rawRole) {
            client->write("LOGIN_RESULT|FAILED|ROLE_MISMATCH\n");
            return;
        }

        // ورود موفق
        clientUsernames[client] = username;

        if (rawRole == "restaurantowner") {
            client->write(QString("LOGIN_RESULT|SUCCESS|%1|%2\n")
                              .arg(user.role)
                              .arg(user.restaurantId).toUtf8());
        } else {
            client->write(QString("LOGIN_RESULT|SUCCESS|%1\n").arg(user.role).toUtf8());
        }
    } else {
        // کاربر وجود ندارد → ساخت حساب جدید
        int restId = (rawRole == "restaurantowner") ? RestaurantData::instance().generateNewId() : -1;
        bool ok = userRepo.addUser(username, password, rawRole, restId);
        if (!ok) {
            client->write("LOGIN_RESULT|FAILED|DB_ERROR\n");
            return;
        }

        clientUsernames[client] = username;

        if (rawRole == "restaurantowner") {
            RestaurantData::instance().addRestaurant(Restaurant(restId, username + "'s Restaurant", ""));
            client->write(QString("LOGIN_RESULT|SUCCESS|%1|%2\n").arg(rawRole).arg(restId).toUtf8());
        } else {
            client->write(QString("LOGIN_RESULT|SUCCESS|%1\n").arg(rawRole).toUtf8());
        }

        qDebug() << "🆕 New user registered:" << username << rawRole;
    }
}

void ServerApp::handleGetRestaurants(QTcpSocket* client)
{
    QString response = RestaurantData::instance().serializeRestaurants();
    client->write(("RESTAURANTS|" + response + "\n").toUtf8());
}

void ServerApp::handleAddOrder(QTcpSocket* client, const QStringList& parts)
{
    client->write("🛒 ADD_ORDER|Feature under development\n");
}

void ServerApp::handleGetMenu(QTcpSocket* client, const QStringList& parts)
{
    if (parts.size() < 2) {
        client->write("MENU|ERROR\n");
        return;
    }

    int restId = parts[1].toInt();
    QList<Food> menu = foodRepo.getFoodsByRestaurant(restId);

    QStringList responseParts;
    for (const Food& food : menu) {
        responseParts << QString("%1~%2~%3~%4")
        .arg(food.getId())
            .arg(food.getName())
            .arg(food.getDescription())
            .arg(food.getPrice());
    }

    client->write(("MENU|" + responseParts.join("|") + "\n").toUtf8());
}

void ServerApp::handleAddFood(QTcpSocket* client, const QStringList& parts)
{
    if (parts.size() < 5) {
        client->write("ADD_FOOD_FAILED|INVALID_FORMAT\n");
        return;
    }

    int restId = parts[1].toInt();
    QString name = parts[2];
    QString desc = parts[3];
    double price = parts[4].toDouble();

    Food food(0, name, desc, price, FoodCategory::FAST_FOOD, "");
    bool ok = foodRepo.addFood(restId, food);
    client->write((ok ? "FOOD_ADDED\n" : "FOOD_ADD_FAILED\n"));
}

void ServerApp::handleGetMyMenu(QTcpSocket* client)
{
    QString username = clientUsernames.value(client);
    if (username.isEmpty()) {
        client->write("❌ GET_MY_MENU_FAILED|Unauthenticated\n");
        return;
    }

    const Restaurant* restaurant = RestaurantData::instance().getRestaurantByOwner(username);
    if (!restaurant) {
        client->write("❌ GET_MY_MENU_FAILED|Restaurant not found\n");
        return;
    }

    QString menu = restaurant->serializeMenu();
    client->write(("MY_MENU|" + menu + "\n").toUtf8());
}

void ServerApp::handleRemoveFood(QTcpSocket* client, const QStringList& parts)
{
    if (parts.size() < 2) {
        client->write("REMOVE_FOOD_FAILED|INVALID_FORMAT\n");
        return;
    }

    int foodId = parts[1].toInt();
    bool ok = foodRepo.removeFood(foodId);
    client->write((ok ? "FOOD_REMOVED\n" : "FOOD_REMOVE_FAILED\n"));
}
