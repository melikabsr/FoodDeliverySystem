#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

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
    QVector<QTcpSocket*> clients;
};

#endif // SERVERAPP_H
