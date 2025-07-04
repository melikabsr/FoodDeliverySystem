#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QObject>
#include <QVector>
#include "ServerOrder.h"

class OrderManager : public QObject
{
    Q_OBJECT

public:
    static OrderManager& instance();  // Singleton

    void addOrder(const ServerOrder& order);
    QVector<ServerOrder> getOrdersForCustomer(const QString& username) const;
    QVector<ServerOrder>& getAllOrders();
    ServerOrder* getOrderById(int id);
    void removeOrder(int orderId);
    int generateNewId();
    int initializeNextIdFromDatabase() ;
private:
    explicit OrderManager(QObject* parent = nullptr);
    QVector<ServerOrder> orders;
    int nextOrderId = 1;
};

#endif // ORDERMANAGER_H
