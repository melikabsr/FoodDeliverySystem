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

int CustomerService::getQuantity(const Food& food) const
{
    int id = food.getId();
    return cart.contains(id) ? cart[id].second : 0;
}

void CustomerService::setCurrentUser(std::shared_ptr<User> user)
{
    currentUser = user;

    bool exists = false;
    for (const auto& u : allUsers) {
        if (u->getUsername() == user->getUsername()) {
            exists = true;
            break;
        }
    }

    if (!exists)
        allUsers.append(user);
}

QString CustomerService::getCurrentUsername() const
{
    return currentUser ? currentUser->getUsername() : "unknown";
}

QList<std::shared_ptr<User>> CustomerService::getAllUsers() const
{
    return allUsers;
}

void CustomerService::removeUser(const QString& username)
{
    for (int i = 0; i < allUsers.size(); ++i) {
        if (allUsers[i]->getUsername() == username) {
            allUsers.removeAt(i);
            break;
        }
    }
}




void CustomerService::removeFromCart(const Food& food)
{
    int id = food.getId();
    if (cart.contains(id)) {
        cart.remove(id);
    }
}




void CustomerService::decreaseQuantity(const Food& food)
{
    int id = food.getId();
    if (cart.contains(id)) {
        int qty = cart[id].second;
        if (qty > 1)
            cart[id].second--;
        else
            cart.remove(id);
    }
}
