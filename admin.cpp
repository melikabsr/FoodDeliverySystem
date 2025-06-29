#include "Admin.h"
#include <QDebug>

Admin::Admin(const QString& username,
             const QString& password,
             const QString& email)
    : User(username, password, email, UserType::ADMIN)
{
}

bool Admin::login(const QString& inputUsername, const QString& inputPassword) {
    return (username == inputUsername && password == inputPassword);
}

void Admin::logout() {
    qDebug() << "Admin" << username << "has logged out.";
}

QString Admin::getInfo() const {
    return QString("👑 Admin:\nUsername: %1\nEmail: %2")
        .arg(username)
        .arg(email);
}
