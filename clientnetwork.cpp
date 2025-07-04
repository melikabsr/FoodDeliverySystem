#include "ClientNetwork.h"
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

void ClientNetwork::onDisconnected()
{
    emit disconnected();
}

void ClientNetwork::onErrorOccurred(QAbstractSocket::SocketError)
{
    emit errorOccurred(socket->errorString());
}

QList<Food> ClientNetwork::parseMenuMessage(const QString& rawData)
{
    QList<Food> result;
    QStringList entries = rawData.split(";", Qt::SkipEmptyParts);
    for (const QString& entry : entries) {
        QStringList parts = entry.split("~");
        if (parts.size() < 4) continue;
        int id = parts[0].toInt();
        QString name = parts[1];
        QString desc = parts[2];
        double price = parts[3].toDouble();
        result.append(Food(id, name, desc, price));
    }
    return result;
}

void ClientNetwork::onReadyRead()
{
    while (socket->canReadLine()) {
        QString msg = QString::fromUtf8(socket->readLine()).trimmed();
        qDebug() << "📥 Received:" << msg;

        if (msg.startsWith("MY_MENU|")) {
            QString payload = msg.section('|', 1);
            QList<Food> menu = parseMenuMessage(payload);
            emit menuReceived(menu);
        }
        else if (msg.startsWith("ORDERS|")) {
            emit ordersUpdated();
        }
        else if (msg.startsWith("LOGIN_RESULT|")) {
            emit messageReceived(msg);
        }
        else {
            emit messageReceived(msg);
        }
    }
}
