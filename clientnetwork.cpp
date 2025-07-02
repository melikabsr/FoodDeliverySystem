#include "clientnetwork.h"
#include <QDebug>

ClientNetwork::ClientNetwork(QObject* parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &ClientNetwork::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientNetwork::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientNetwork::onErrorOccurred);
}

bool ClientNetwork::connectToServer(const QString& host, quint16 port)
{
    socket->connectToHost(host, port);
    return socket->waitForConnected(3000);
}

void ClientNetwork::sendMessage(const QString& message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write((message + "\n").toUtf8());
    }
}

bool ClientNetwork::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void ClientNetwork::onReadyRead()
{
    while (socket->canReadLine()) {
        QString msg = QString::fromUtf8(socket->readLine()).trimmed();
        emit messageReceived(msg);
    }
}

void ClientNetwork::onDisconnected()
{
    emit disconnected();
}

void ClientNetwork::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit errorOccurred(socket->errorString());
}
