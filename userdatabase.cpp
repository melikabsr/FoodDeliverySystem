#include "UserDatabase.h"

UserDatabase::UserDatabase(QObject* parent)
    : QObject(parent)
{
    // کاربران نمونه برای تست اولیه
    addUser("ali", "1234", "CUSTOMER");
    addUser("sara", "pass", "RESTAURANT_OWNER");
    addUser("admin", "admin", "ADMIN");
}

UserDatabase& UserDatabase::instance()
{
    static UserDatabase db;
    return db;
}

void UserDatabase::addUser(const QString& username, const QString& password, const QString& role)
{
    users[username] = qMakePair(password, role);
}

bool UserDatabase::validateLogin(const QString& username, const QString& password) const
{
    if (users.contains(username)) {
        return users[username].first == password;
    }
    return false;
}

QString UserDatabase::getRole(const QString& username) const
{
    return users.value(username).second;
}
