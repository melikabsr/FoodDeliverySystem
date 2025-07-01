#include "OrderManager.h"

OrderManager::OrderManager(QObject* parent)
    : QObject(parent) {}

OrderManager& OrderManager::instance()
{
    static OrderManager manager;
    return manager;
}

void OrderManager::addOrder(const Order& order)
{
    orders.append(order);
}

QVector<Order> OrderManager::getOrdersForUser(const QString& username) const
{
    QVector<Order> result;
    for (const Order& o : orders) {
        if (o.username == username)
            result.append(o);
    }
    return result;
}

QVector<Order> OrderManager::getAllOrders() const
{
    return orders;
}

void OrderManager::removeOrder(int id)
{
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].id == id) {
            orders.removeAt(i);
            break;
        }
    }
}

int OrderManager::generateNewId() const
{
    int maxId = 0;
    for (const auto& o : orders) {
        if (o.id > maxId)
            maxId = o.id;
    }
    return maxId + 1;
}
