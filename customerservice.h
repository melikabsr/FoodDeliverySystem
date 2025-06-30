#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <QMap>
#include <QPair>
#include <memory>
#include "Food.h"
#include "User.h"

class CustomerService
{
public:
    static CustomerService& instance();
    void removeUser(const QString& username);

    void addToCart(const Food& food);
    void removeItem(int id);
    void clearCart();
    QMap<int, QPair<Food, int>> getCartItems() const;

    void setCurrentUser(std::shared_ptr<User> user);
    QString getCurrentUsername() const;
    QList<std::shared_ptr<User>> getAllUsers() const;

private:

    QList<std::shared_ptr<User>> allUsers;

    CustomerService() = default;
    QMap<int, QPair<Food, int>> cart;
    std::shared_ptr<User> currentUser;
};

#endif // CUSTOMERSERVICE_H



