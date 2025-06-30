#include "userlistwidget.h"
#include "CustomerService.h"
#include "User.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

UserListWidget::UserListWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("👥 All Registered Users");
    resize(450, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("📋 لیست کاربران سامانه:");
    title->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(title);

    auto users = CustomerService::instance().getAllUsers();

    for (const auto& user : users) {
        QString typeStr;
        switch (user->getUserType()) {
        case UserType::CUSTOMER: typeStr = "👤 Customer"; break;
        case UserType::RESTAURANT_OWNER: typeStr = "🍽️ Restaurant Owner"; break;
        case UserType::ADMIN: typeStr = "🛡️ Admin"; break;
        }

        QString info = QString("%1 (%2) - %3").arg(user->getUsername(), user->getEmail(), typeStr);

        QWidget* row = new QWidget(this);
        QHBoxLayout* rowLayout = new QHBoxLayout(row);

        QLabel* label = new QLabel(info, this);
        QPushButton* removeBtn = new QPushButton("❌ Remove", this);

        connect(removeBtn, &QPushButton::clicked, [=]() {
            if (user->getUserType() == UserType::ADMIN) {
                QMessageBox::warning(this, "Access Denied", "🚫 Cannot delete admin user.");
                return;
            }
            CustomerService::instance().removeUser(user->getUsername());
            row->hide();
        });

        rowLayout->addWidget(label);
        rowLayout->addWidget(removeBtn);
        row->setLayout(rowLayout);
        layout->addWidget(row);
    }
}

