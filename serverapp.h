#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class ServerApp : public QObject
{
    Q_OBJECT
public:
    explicit ServerApp(QObject *parent = nullptr);
    void startServer(quint16 port = 1234);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer* server;
    QMap<QTcpSocket*, QString> clientUsernames;
    void handleGetMenu(QTcpSocket* client, const QStringList& parts);

    void handleMessage(QTcpSocket* client, const QString& message);
    void handleLogin(QTcpSocket* client, const QStringList& parts);
    void handleGetRestaurants(QTcpSocket* client);
    void handleAddOrder(QTcpSocket* client, const QStringList& parts);
};

#endif // SERVERAPP_H
