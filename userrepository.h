#ifndef USERREPOSITORY
#define USERREPOSITORY
#include <QString>
#include <optional>

struct UserData {
    QString username;
    QString password;
    QString role;
    int restaurantId;
};

class UserRepository
{
public:
    bool addUser(const QString& username, const QString& password, const QString& role, int restaurantId);
    bool userExists(const QString& username) const;
    bool validateLogin(const QString& username, const QString& password) const;
    std::optional<UserData> getUser(const QString& username, const QString& role) const;
    bool removeUser(const QString& username);
};

#endif
