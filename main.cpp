#include <QApplication>
#include <QDebug>
#include <memory>
#include <vector>

#include "Customer.h"
#include "RestaurantOwner.h"
#include "Admin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // استفاده از std::vector به جای QList برای پشتیبانی از move semantics
    std::vector<std::unique_ptr<User>> users;

    users.push_back(std::make_unique<Customer>("ali123", "pass1", "ali@example.com"));
    users.push_back(std::make_unique<RestaurantOwner>("reza_owner", "pass2", "reza@foodhub.com"));
    users.push_back(std::make_unique<Admin>("adminboss", "adminpass", "admin@panel.com"));

    for (const auto& user : users) {
        qDebug() << "----------------------------";

        bool success = user->login(user->getUsername(), "wrongpass");
        qDebug() << "Login with wrong password:" << (success ? "✅ Success" : "❌ Failed");

        success = user->login(user->getUsername(), "pass1");
        qDebug() << "Login with correct password:" << (success ? "✅ Success" : "❌ Failed");

        qDebug().noquote() << user->getInfo();
        user->logout();
    }

    return 0;
}
