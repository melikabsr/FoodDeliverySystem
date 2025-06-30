#ifndef RESTAURANTOWNER_H
#define RESTAURANTOWNER_H

#include "User.h"
#include "enums.h"

class RestaurantOwner : public User {
public:
    RestaurantOwner(const QString& username,
                    const QString& password,
                    const QString& email);

    // override virtual functions
    bool login(const QString& inputUsername, const QString& inputPassword) override;
    void logout() override;
    QString getInfo() const override;
};

#endif // RESTAURANTOWNER_H
