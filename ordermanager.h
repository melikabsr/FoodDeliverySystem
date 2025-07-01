#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "Food.h"

struct Order
{
    int id;
    QString username;
    QMap<int, QPair<Food, int>> items; // key = foodId, value = (food, quantity)
};

class OrderManager : public QObject
{
    Q_OBJECT

public:
    static OrderManager& instance();

    void addOrder(const Order& order);
    QVector<Order> getOrdersForUser(const QString& username) const;
    QVector<Order> getAllOrders() const;
    void removeOrder(int id);
    int generateNewId() const;

private:
    explicit OrderManager(QObject* parent = nullptr);
    QVector<Order> orders;
};

#endif // ORDERMANAGER_H
