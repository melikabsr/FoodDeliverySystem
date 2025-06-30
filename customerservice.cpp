#include "CustomerService.h"

CustomerService& CustomerService::instance()
{
    static CustomerService service;
    return service;
}

void CustomerService::addToCart(const Food& food)
{
    int id = food.getId();
    if (cart.contains(id)) {
        cart[id].second += 1;
    } else {
        cart.insert(id, qMakePair(food, 1));
    }
}

void CustomerService::removeItem(int id)
{
    cart.remove(id);
}

void CustomerService::clearCart()
{
    cart.clear();
}

QMap<int, QPair<Food, int>> CustomerService::getCartItems() const
{
    return cart;
}

void CustomerService::setCurrentUser(std::shared_ptr<User> user)
{
    currentUser = user;
}

QString CustomerService::getCurrentUsername() const
{
    return currentUser ? currentUser->getUsername() : "unknown";
}
