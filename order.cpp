#include "Order.h"

Order::Order()
    : id(0), status(OrderStatus::PENDING), totalAmount(0.0), customerUsername("") {}

Order::Order(int id, const QString& customerUsername)
    : id(id), status(OrderStatus::PENDING), totalAmount(0.0), customerUsername(customerUsername) {}

void Order::addItem(const Food& food, int quantity)
{
    int foodId = food.getId();
    if (items.contains(foodId)) {
        items[foodId].second += quantity;
    } else {
        items.insert(foodId, qMakePair(food, quantity));
    }

    calculateTotal();
}

void Order::calculateTotal()
{
    totalAmount = 0;
    for (const auto& pair : items) {
        totalAmount += pair.first.getPrice() * pair.second;
    }
}

int Order::getId() const { return id; }

OrderStatus Order::getStatus() const { return status; }

void Order::setStatus(OrderStatus newStatus) { status = newStatus; }

double Order::getTotalAmount() const { return totalAmount; }

QMap<int, QPair<Food, int>> Order::getItems() const { return items; }

QString Order::getCustomerUsername() const { return customerUsername; }
