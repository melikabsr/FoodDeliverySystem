#include "CustomerPanel.h"
#include <QMessageBox>
#include <QApplication>
#include "RestaurantListWidget.h"
#include "ShoppingCartWidget.h"
#include "OrderHistoryWidget.h"

CustomerPanel::CustomerPanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("🍽️ Welcome, dear customer!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    viewRestaurantsButton = new QPushButton("Browse Restaurants");
    viewCartButton = new QPushButton("View Shopping Cart");
    viewOrdersButton = new QPushButton("📜 View Order History");
    logoutButton = new QPushButton("Logout");

    layout->addWidget(welcomeLabel);
    layout->addWidget(viewRestaurantsButton);
    layout->addWidget(viewCartButton);
    layout->addWidget(viewOrdersButton);
    layout->addWidget(logoutButton);

    connect(viewRestaurantsButton, &QPushButton::clicked, [this]() {
        auto* listWidget = new RestaurantListWidget();
        listWidget->setWindowTitle("Available Restaurants");
        listWidget->resize(400, 400);
        listWidget->show();
    });

    connect(viewCartButton, &QPushButton::clicked, [=]() {
        auto* cart = new ShoppingCartWidget();
        cart->setWindowTitle("🛒 Your Cart");
        cart->resize(400, 400);
        cart->show();
    });

    connect(viewOrdersButton, &QPushButton::clicked, this, &CustomerPanel::showOrderHistory);

    connect(logoutButton, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Logout", "Logging out...");
        qApp->exit(); // موقتی
    });
}

void CustomerPanel::showOrderHistory()
{
    auto* history = new OrderHistoryWidget();
    history->setWindowTitle("📜 Order History");
    history->resize(450, 500);
    history->show();
}
