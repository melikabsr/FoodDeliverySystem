#include "RestaurantOwner.h"
#include <QDebug>

RestaurantOwner::RestaurantOwner(const QString& username,
                                 const QString& password,
                                 const QString& email)
    : User(username, password, email, UserType::RESTAURANT_OWNER)
{
}

bool RestaurantOwner::login(const QString& inputUsername, const QString& inputPassword) {
    return (username == inputUsername && password == inputPassword);
}

void RestaurantOwner::logout() {
    qDebug() << "Restaurant Owner" << username << "has logged out.";
}

QString RestaurantOwner::getInfo() const {
    return QString("🍽️ Restaurant Owner:\nUsername: %1\nEmail: %2")
        .arg(username)
        .arg(email);
}
