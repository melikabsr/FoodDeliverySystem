#ifndef DEBUGTESTWINDOW_H
#define DEBUGTESTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "RestaurantListWidget.h"
#include "ShoppingCartWidget.h"
#include "OrderHistoryWidget.h"
#include "AdminPanel.h"
#include "CustomerPanel.h"
#include "RestaurantOwnerPanel.h"

class DebugTestWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DebugTestWindow(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setWindowTitle("🧪 Debug Test Panel");
        resize(300, 400);

        auto* layout = new QVBoxLayout(this);

        QPushButton* btnCustomerPanel = new QPushButton("👤 CustomerPanel");
        QPushButton* btnAdminPanel = new QPushButton("🛡️ AdminPanel");
        QPushButton* btnRestaurantPanel = new QPushButton("🍽️ RestaurantOwnerPanel");
        QPushButton* btnRestaurants = new QPushButton("📋 Restaurant List");
        QPushButton* btnCart = new QPushButton("🛒 Shopping Cart");
        QPushButton* btnOrders = new QPushButton("📜 Order History");

        layout->addWidget(btnCustomerPanel);
        layout->addWidget(btnAdminPanel);
        layout->addWidget(btnRestaurantPanel);
        layout->addWidget(btnRestaurants);
        layout->addWidget(btnCart);
        layout->addWidget(btnOrders);

        connect(btnCustomerPanel, &QPushButton::clicked, []() {
            auto* w = new CustomerPanel();
            w->show();
        });

        connect(btnAdminPanel, &QPushButton::clicked, []() {
            auto* w = new AdminPanel();
            w->show();
        });

        connect(btnRestaurantPanel, &QPushButton::clicked, []() {
            auto* w = new RestaurantOwnerPanel();
            w->show();
        });

        connect(btnRestaurants, &QPushButton::clicked, []() {
            auto* w = new RestaurantListWidget();
            w->show();
        });

        connect(btnCart, &QPushButton::clicked, []() {
            auto* w = new ShoppingCartWidget();
            w->show();
        });

        connect(btnOrders, &QPushButton::clicked, []() {
            auto* w = new OrderHistoryWidget();
            w->show();
        });
    }
};

#endif // DEBUGTESTWINDOW_H
