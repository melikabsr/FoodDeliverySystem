#include "OrderManager.h"

OrderManager::OrderManager(QObject* parent)
    : QObject(parent) {}

OrderManager& OrderManager::instance()
{
    static OrderManager instance;
    return instance;
}

void OrderManager::addOrder(const Order& order)
{
    orders.append(order);
}

QVector<Order> OrderManager::getOrdersForCustomer(const QString& username) const
{
    QVector<Order> result;
    for (const Order& o : orders) {
        if (o.getCustomerUsername() == username)
            result.append(o);
    }
    return result;
}

QVector<Order>& OrderManager::getAllOrders()
{
    return orders;
}

Order* OrderManager::getOrderById(int id)
{
    for (Order& o : orders) {
        if (o.getId() == id)
            return &o;
    }
    return nullptr;
}


void OrderManager::removeOrder(int orderId)
{
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == orderId) {
            orders.removeAt(i);
            break;
        }
    }
}

