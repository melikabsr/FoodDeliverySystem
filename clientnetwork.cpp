#include "ClientNetwork.h"
#include <QDebug>
#include <QRegularExpression>
#include "ClientDatabaseManager.h"

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

// void ClientNetwork::onReadyRead()
// {
//     while (socket->canReadLine()) {
//         QString msg = QString::fromUtf8(socket->readLine()).trimmed();
//         qDebug() << "📥 Message from server:" << msg;

//         if (msg.startsWith("MENU|")) {
//             QString data = msg.section('|', 1);
//             QList<Food> parsedMenu = parseMenuMessage(data);
//             emit menuReceived(parsedMenu);
//         } else {
//             emit messageReceived(msg);  // سایر پیام‌ها
//         }
//     }
// }

void ClientNetwork::onDisconnected()
{
    emit disconnected();
}

void ClientNetwork::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit errorOccurred(socket->errorString());
}

QList<Food> ClientNetwork::parseMenuMessage(const QString& rawData)
{
    QList<Food> result;

    QStringList foodEntries = rawData.split(";");
    for (const QString& entry : foodEntries) {
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






QList<Food> parseMenu(const QString& data) {
    QList<Food> menu;
    QStringList items = data.split(";");
    for (const QString& item : items) {
        QStringList parts = item.split(",");
        if (parts.size() >= 4) {
            int id = parts[0].toInt();
            QString name = parts[1];
            QString desc = parts[2];
            double price = parts[3].toDouble();
            menu.append(Food(id, name, desc, price, FoodCategory::FAST_FOOD,  QString("")));
        }
    }
    return menu;
}



// void ClientNetwork::onReadyRead()
// {
//     while (socket->canReadLine()) {
//         QString msg = QString::fromUtf8(socket->readLine()).trimmed();

//         if (msg.startsWith("MY_MENU|")) {
//             QString payload = msg.section('|', 1);
//             QList<Food> menu = parseMenu(payload);
//             emit menuReceived(menu);
//         } else if (msg.startsWith("ORDERS|")) {
//             QString raw = msg.section('|', 1);
//             QStringList orderEntries = raw.split(";");

//             for (const QString& entry : orderEntries) {
//                 // مثال ورودی: 🧾 Order #101 - Total: 34000 تومان - [Burger×2, Coke×1]
//                 QRegularExpression re("Order #(\\d+) - Total: (\\d+) تومان - \\[(.+)\\]");
//                 QRegularExpressionMatch match = re.match(entry);
//                 if (match.hasMatch()) {
//                     int orderId = match.captured(1).toInt();
//                     double total = match.captured(2).toDouble();
//                     QString items = match.captured(3);

//                     if (!ClientDatabaseManager::instance().orderExists(orderId)) {
//                         ClientDatabaseManager::instance().saveOrder(orderId, "PENDING", total, items);
//                     }
//                 }
//             }

//             emit ordersUpdated();  // سیگنالی برای آپدیت UI (مثلاً لیست سفارش‌ها)
//         } else {
//             emit messageReceived(msg);  // سایر پیام‌ها
//         }
//     }
// }



void ClientNetwork::onReadyRead()
{
    while (socket->canReadLine()) {
        QString msg = QString::fromUtf8(socket->readLine()).trimmed();

        if (msg.startsWith("MY_MENU|")) {
            QString payload = msg.section('|', 1);
            QList<Food> menu = parseMenuMessage(payload);

            emit menuReceived(menu);
        } else if (msg.startsWith("ORDERS|")) {
            QString raw = msg.section('|', 1);
            QStringList orderEntries = raw.split(";");

            for (const QString& entry : orderEntries) {
                QRegularExpression re(R"(#(\d+)\s*-\s*Total:\s*(\d+)\s*تومان\s*-\s*\[(.+)\])");
                QRegularExpressionMatch match = re.match(entry);
                if (match.hasMatch()) {
                    int id = match.captured(1).toInt();
                    double total = match.captured(2).toDouble();
                    QString items = match.captured(3);

                    if (!ClientDatabaseManager::instance().orderExists(id)) {
                        ClientDatabaseManager::instance().saveOrder(id, "PENDING", total, items);
                    }
                }
            }

            emit ordersUpdated();
        } else {
            emit messageReceived(msg);
        }
    }
}
