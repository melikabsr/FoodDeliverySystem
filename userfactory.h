#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <memory>
#include <QString>
#include "User.h"
#include "Customer.h"
#include "RestaurantOwner.h"
#include "Admin.h"
#include "enums.h"

class UserFactory {
public:
    static std::unique_ptr<User> createUser(UserType type,
                                            const QString& username,
                                            const QString& password,
                                            const QString& email);
};

#endif // USERFACTORY_H
