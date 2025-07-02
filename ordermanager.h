#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "Food.h"
#include "ServerOrder.h"
// struct Order
// {
//     int id;
//     QString username;
//     QMap<int, QPair<Food, int>> items;
// };

class OrderManager : public QObject
{
    Q_OBJECT

public:
    static OrderManager& instance();

    QVector<ServerOrder> getOrdersForCustomer(const QString& username) const;
    QVector<ServerOrder> getAllOrders() const;
    void removeOrder(int id);
    int generateNewId() const;
    void addOrder(const ServerOrder& order) ;

private:
    explicit OrderManager(QObject* parent = nullptr);
    QVector<ServerOrder> orders;
};

#endif // ORDERMANAGER_H

