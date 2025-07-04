#include "OrderManager.h"
#include "OrderPersistence.h"
OrderManager::OrderManager(QObject* parent)
    : QObject(parent) {}

OrderManager& OrderManager::instance()
{
    static OrderManager instance;
    return instance;
}

void OrderManager::addOrder(const ServerOrder& order)
{
    orders.append(order);
    OrderPersistence::saveOrderToDatabase(order);
}


QVector<ServerOrder> OrderManager::getOrdersForCustomer(const QString& username) const
{
    QVector<ServerOrder> result;
    for (const ServerOrder& o : orders) {
        if (o.getCustomerUsername() == username)
            result.append(o);
    }
    return result;
}

QVector<ServerOrder>& OrderManager::getAllOrders()
{
    return orders;
}

ServerOrder* OrderManager::getOrderById(int id)
{
    for (ServerOrder& o : orders) {
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

int OrderManager::generateNewId()
{
    return nextOrderId++;
}


int OrderManager::initializeNextIdFromDatabase()
{
    nextOrderId = OrderPersistence::loadMaxOrderId() + 1;
    return nextOrderId;
}
