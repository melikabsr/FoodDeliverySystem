#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QThread>
#include <QTcpSocket>

class ClientHandler : public QThread
{
    Q_OBJECT
public:
    explicit ClientHandler(QTcpSocket* socket, QObject* parent = nullptr);
    void run() override;

private:
    QTcpSocket* socket;
    QString username;
    void handleAddOrder(const QStringList& parts);

    void processMessage(const QString& msg);
    void handleLogin(const QStringList& parts);
    void handleGetRestaurants();
    void handleGetMenu(const QStringList& parts);
};

#endif // CLIENTHANDLER_H
