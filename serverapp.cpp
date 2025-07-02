#include "ServerApp.h"
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
        qCritical() << "❌ Failed to start server:" << server->errorString();
    } else {
        qDebug() << "✅ Server started on port" << port;
    }
}

void ServerApp::onNewConnection()
{
    QTcpSocket* client = server->nextPendingConnection();
    clients.append(client);

    connect(client, &QTcpSocket::readyRead, this, &ServerApp::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ServerApp::onClientDisconnected);

    qDebug() << "📥 New client connected:" << client->peerAddress().toString();
}

void ServerApp::onClientDisconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(client);
    client->deleteLater();
    qDebug() << "📤 Client disconnected.";
}

void ServerApp::onReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    qDebug() << "📨 Received from client:" << QString::fromUtf8(data);
}
