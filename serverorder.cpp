
#include "ServerOrder.h"

ServerOrder::ServerOrder(int id, const QString& username)
    : orderId(id), customerUsername(username) {}

int ServerOrder::getId() const {
    return orderId;
}

QString ServerOrder::getCustomerUsername() const {
    return customerUsername;
}

void ServerOrder::addItem(const Food& food, int quantity) {
    items.append(qMakePair(food, quantity));
}

QList<QPair<Food, int>> ServerOrder::getItems() const {
    return items;
}

double ServerOrder::getTotalAmount() const {
    double total = 0;
    for (const auto& pair : items) {
        total += pair.first.getPrice() * pair.second;
    }
    return total;
}
