#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>

class ClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetwork(QObject* parent = nullptr);
    bool connectToServer(const QString& host, quint16 port);
    void sendMessage(const QString& message);
    bool isConnected() const;

signals:
    void messageReceived(const QString& message);
    void disconnected();
    void errorOccurred(const QString& error);

private slots:
    void onReadyRead();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* socket;
};

#endif // CLIENTNETWORK_H
