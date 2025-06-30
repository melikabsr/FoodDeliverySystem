#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <QList>
#include <QPair>
#include "Food.h"
#include <enums.h>

class CustomerService
{
public:
    static CustomerService& instance();

    void addToCart(const Food& food);
    QList<QPair<Food, int>> getCartItems() const;
    void clearCart();
    void removeItem(int id);

private:
    CustomerService(); // Singleton
    QList<QPair<Food, int>> cart;
};

#endif // CUSTOMERSERVICE_H

