#include "CustomerPanel.h"
#include <QMessageBox>
#include <QApplication>
#include "RestaurantListWidget.h"
#include "ShoppingCartWidget.h"
#include "OrderHistoryWidget.h"
#include "ClientDatabaseManager.h"
CustomerPanel::CustomerPanel(ClientNetwork* net, const QString& username, QWidget *parent)
    : QWidget(parent), network(net), username(username)
{
    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("🍽️ Welcome, dear customer!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(welcomeLabel);

    orderListWidget = new QListWidget(this);
    mainLayout->addWidget(orderListWidget);

    viewRestaurantsButton = new QPushButton("📋 Browse Restaurants");
    viewCartButton = new QPushButton("🛒 View Shopping Cart");
    viewOrdersButton = new QPushButton("📜 View Order History");
    logoutButton = new QPushButton("🚪 Logout");

    mainLayout->addWidget(viewRestaurantsButton);
    mainLayout->addWidget(viewCartButton);
    mainLayout->addWidget(viewOrdersButton);
    mainLayout->addWidget(logoutButton);

    // اتصال سیگنال‌ها
    connect(viewRestaurantsButton, &QPushButton::clicked, [=]() {
        auto* listWidget = new RestaurantListWidget(network, username);
        listWidget->show();
    });

    connect(viewCartButton, &QPushButton::clicked, [=]() {
        auto* cart = new ShoppingCartWidget(network, username);
        cart->show();
    });

    connect(viewOrdersButton, &QPushButton::clicked, this, &CustomerPanel::showOrderHistory);

    connect(logoutButton, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Logout", "Logging out...");
        qApp->exit();
    });
}

void CustomerPanel::showOrderHistory()
{
    auto* history = new OrderHistoryWidget(network, username);
    history->setWindowTitle("📜 Order History");
    history->resize(450, 500);
    history->show();
}





void CustomerPanel::refreshOrders()
{
    orderListWidget->clear();
    QList<QMap<QString, QVariant>> orders = ClientDatabaseManager::instance().getAllOrders();
    for (const auto& order : orders) {
        QString text = QString("سفارش #%1 - %2 تومان\nاقلام: %3")
                           .arg(order["id"].toInt())
                           .arg(order["total"].toDouble())
                           .arg(order["items"].toString());
        orderListWidget->addItem(text);
    }
}
