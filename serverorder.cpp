#include "ServerOrder.h"
ServerOrder::ServerOrder(int id, const QString& username)
    : orderId(id), customerUsername(username), status(OrderStatus::PENDING),
    timestamp(QDateTime::currentDateTime()) {}


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

OrderStatus ServerOrder::getStatus() const {
    return status;
}

void ServerOrder::setStatus(OrderStatus newStatus) {
    status = newStatus;
}



QDateTime ServerOrder::getTimestamp() const {
    return timestamp;
}

void ServerOrder::setTimestamp(const QDateTime& t) {
    timestamp = t;
}


OrderStatus ServerOrder::fromString(const QString& s) {
    QString val = s.trimmed().toUpper();
    if (val == "PENDING") return OrderStatus::PENDING;
    if (val == "PREPARING") return OrderStatus::PREPARING;
    if (val == "READY") return OrderStatus::READY;
    if (val == "DELIVERED") return OrderStatus::DELIVERED;
    if (val == "CANCELLED") return OrderStatus::CANCELLED;
    return OrderStatus::PENDING;
}


QString ServerOrder::statusToString(OrderStatus status) {
    switch (status) {
    case OrderStatus::PENDING_CONFIRMATION: return "PENDING_CONFIRMATION";
    case OrderStatus::CONFIRMED: return "CONFIRMED";
    case OrderStatus::PREPARING: return "PREPARING";
    case OrderStatus::READY: return "READY";
    case OrderStatus::DELIVERED: return "DELIVERED";
    case OrderStatus::PENDING: return "PENDING";
    case OrderStatus::CANCELLED: return "CANCELLED";
    default: return "UNKNOWN";
    }
}
