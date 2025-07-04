#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include "FoodRepository.h"
#include "RestaurantRepository.h"
#include "UserRepository.h"

class ServerApp : public QObject
{
    Q_OBJECT

public:
    explicit ServerApp(QObject *parent = nullptr);
    bool startServer(quint16 port = 1234);  // شروع سرور

private slots:
    void onNewConnection();                 // اتصال کلاینت جدید
    void onClientDisconnected();            // قطع اتصال کلاینت
    void onReadyRead();                     // دریافت پیام

private:
    QTcpServer* server;
    QMap<QTcpSocket*, QString> clientUsernames;

    FoodRepository foodRepo;
    RestaurantRepository restaurantRepo;
    UserRepository userRepo;

    // مدیریت دستورات
    void handleMessage(QTcpSocket* client, const QString& message);
    void handleLogin(QTcpSocket* client, const QStringList& parts);
    void handleGetRestaurants(QTcpSocket* client);
    void handleAddOrder(QTcpSocket* client, const QStringList& parts);
    void handleGetMenu(QTcpSocket* client, const QStringList& parts);
    void handleAddFood(QTcpSocket* client, const QStringList& parts);
    void handleGetMyMenu(QTcpSocket* client);
    void handleRemoveFood(QTcpSocket* client, const QStringList& parts);
};

#endif // SERVERAPP_H
