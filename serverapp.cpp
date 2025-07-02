#include "ServerApp.h"
#include "UserDatabase.h"
#include "RestaurantData.h"
 #include <QTcpServer>
#include <QDebug>

ServerApp::ServerApp(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &ServerApp::onNewConnection);
}

void ServerApp::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) {
        qCritical() << "❌ Server failed to start:" << server->errorString();
    } else {
        qDebug() << "✅ Server started on port" << port;
    }
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
    QString data = QString::fromUtf8(client->readAll()).trimmed();
    qDebug() << "📨 Received:" << data;
    handleMessage(client, data);
}

void ServerApp::handleMessage(QTcpSocket* client, const QString& message)
{
    QStringList parts = message.split("|");
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    if (command == "LOGIN") {
        handleLogin(client, parts);
    } else if (command == "GET_RESTAURANTS") {
        handleGetRestaurants(client);
    } else if (command == "ADD_ORDER") {
        handleAddOrder(client, parts);
    }else if  (command == "GET_MENU") {
        handleGetMenu(client, parts);
    } else  {
        client->write("❓ Unknown command\n");
    }

}

void ServerApp::handleLogin(QTcpSocket* client, const QStringList& parts)
{
    if (parts.size() < 3) {
        client->write("❌ LOGIN|Missing fields\n");
        return;
    }

    QString username = parts[1];
    QString password = parts[2];

    if (UserDatabase::instance().validateLogin(username, password)) {
        clientUsernames[client] = username;
        client->write("✅ LOGIN|SUCCESS\n");
    } else {
        client->write("❌ LOGIN|FAILED\n");
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


#include "restaurantdata.h"  // اطمینان از این که RestaurantData قابل دسترس است

void ServerApp::handleGetMenu(QTcpSocket* client, const QList<QString>& parts)
{
    if (parts.size() < 2) {
        client->write("❌ Missing restaurant ID.\n");
        return;
    }

    bool ok;
    int restaurantId = parts[1].toInt(&ok);
    if (!ok) {
        client->write("❌ Invalid restaurant ID format.\n");
        return;
    }

    const Restaurant* r = RestaurantData::instance().getRestaurantById(restaurantId);
    if (!r) {
        client->write("❌ Restaurant not found.\n");
        return;
    }

    QString serializedMenu = r->serializeMenu();
    client->write(QString("✅ MENU|%1\n").arg(serializedMenu).toUtf8());
}



bool ServerApp::start(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qCritical() << "❌ Server failed to start on port" << port << ":" << tcpServer->errorString();
        return false;
    }

    qDebug() << "✅ Server started successfully on port" << port;
    return true;
}
