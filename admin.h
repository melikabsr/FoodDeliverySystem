#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(const QString& username,
          const QString& password,
          const QString& email);

    // override virtual functions
    bool login(const QString& inputUsername, const QString& inputPassword) override;
    void logout() override;
    QString getInfo() const override;
};

#endif // ADMIN_H
