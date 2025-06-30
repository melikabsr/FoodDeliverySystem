#include "CustomerService.h"

CustomerService::CustomerService() {}

CustomerService& CustomerService::instance()
{
    static CustomerService service;
    return service;
}

void CustomerService::addToCart(const Food& food)
{
    for (auto& item : cart) {
        if (item.first.getId() == food.getId()) {
            item.second += 1;
            return;
        }
    }
    cart.append(qMakePair(food, 1));
}

QList<QPair<Food, int>> CustomerService::getCartItems() const
{
    return cart;
}

void CustomerService::clearCart()
{
    cart.clear();
}
