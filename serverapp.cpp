#include "ServerApp.h"
#include "UserDatabase.h"
#include "RestaurantData.h"

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
    } else if {
        client->write("❓ Unknown command\n");
    } else (command == "GET_MENU") {
        handleGetMenu(client, parts);
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
