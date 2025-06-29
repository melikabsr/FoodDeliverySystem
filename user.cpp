#include "User.h"

// Constructor
User::User(const QString& username,
           const QString& password,
           const QString& email,
           UserType type)
    : username(username), password(password), email(email), userType(type)
{
}

// Getters
QString User::getUsername() const {
    return username;
}

QString User::getEmail() const {
    return email;
}

UserType User::getUserType() const {
    return userType;
}

// Setters
void User::setUsername(const QString& newUsername) {
    username = newUsername;
}

void User::setPassword(const QString& newPassword) {
    password = newPassword;
}

void User::setEmail(const QString& newEmail) {
    email = newEmail;
}

// Virtual method - optional override
QString User::getInfo() const {
    return QString("Username: %1\nEmail: %2\nType: %3")
    .arg(username)
        .arg(email)
        .arg(static_cast<int>(userType));
}
