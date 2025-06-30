#include "UserFactory.h"

std::unique_ptr<User> UserFactory::createUser(UserType type,
                                              const QString& username,
                                              const QString& password,
                                              const QString& email)
{
    switch (type) {
    case UserType::CUSTOMER:
        return std::make_unique<Customer>(username, password, email);
    case UserType::RESTAURANT_OWNER:
        return std::make_unique<RestaurantOwner>(username, password, email);
    case UserType::ADMIN:
        return std::make_unique<Admin>(username, password, email);
    default:
        return nullptr;
    }
}
