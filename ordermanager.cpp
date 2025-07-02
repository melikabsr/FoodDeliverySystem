#include "OrderManager.h"
//#include "order.h"
OrderManager::OrderManager(QObject* parent)
    : QObject(parent) {}


OrderManager& OrderManager::instance() {
    static OrderManager instance;
    return instance;
}

void OrderManager::addOrder(const ServerOrder& order) {
    orders.append(order);
}


void OrderManager::removeOrder(int id) {
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == id) {
            orders.removeAt(i);
            return;
        }
    }
}

int OrderManager::generateNewId() const {
    return orders.size() + 1;
}





QVector<ServerOrder> OrderManager::getOrdersForCustomer(const QString& username) const {
    QVector<ServerOrder> result;
    for (const ServerOrder& order : orders) {
        if (order.getCustomerUsername() == username) {
            result.append(order);
        }
    }
    return result;
}

QVector<ServerOrder> OrderManager::getAllOrders() const {
    return orders;
}








