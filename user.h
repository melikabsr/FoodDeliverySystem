#ifndef USER_H
#define USER_H

#include <QString>
#include <memory>
#include "enums.h"

class User {
protected:
    QString username;
    QString password;
    QString email;
    UserType userType;
      Role role;
public:
    // Constructor
    User(const QString& username,
         const QString& password,
         const QString& email,
         UserType type);
     User(const QString& username, Role role) : username(username), role(role) {}
    // Virtual destructor for proper cleanup in derived classes
    virtual ~User() = default;

    // Pure virtual functions
    virtual bool login(const QString& inputUsername, const QString& inputPassword) = 0;
    virtual void logout() = 0;

    // Getters
    QString getUsername() const;
    QString getEmail() const;
    UserType getUserType() const;

    // Setters
    void setUsername(const QString& newUsername);
    void setPassword(const QString& newPassword);
    void setEmail(const QString& newEmail);

    // Virtual method that derived classes can override
    virtual QString getInfo() const;
};

#endif // USER_H
