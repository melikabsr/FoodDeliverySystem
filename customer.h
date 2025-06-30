#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <enums.h>

class Customer : public User {
public:
    Customer(const QString& username,
             const QString& password,
             const QString& email);

    // override virtual functions
    bool login(const QString& inputUsername, const QString& inputPassword) override;
    void logout() override;
    QString getInfo() const override;
};

#endif // CUSTOMER_H
