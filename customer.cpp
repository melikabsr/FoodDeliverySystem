#include "Customer.h"
#include <QDebug>

Customer::Customer(const QString& username,
                  const QString& password,
                    const QString& email)
    : User(username, password, email, UserType::CUSTOMER)
 {
}

bool Customer::login(const QString& inputUsername, const QString& inputPassword) {
    // ساده‌ترین مدل اعتبارسنجی (در آینده AuthManager جایگزین می‌شود)
    return (username == inputUsername && password == inputPassword);
}

void Customer::logout() {
    qDebug() << "Customer" << username << "has logged out.";
}

QString Customer::getInfo() const {
    return QString("👤 Customer:\nUsername: %1\nEmail: %2")
        .arg(username)
        .arg(email);
}


