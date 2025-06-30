#include "CustomerPanel.h"
#include <QMessageBox>
#include <QApplication>
#include "RestaurantListWidget.h"
CustomerPanel::CustomerPanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("🍽️ Welcome, dear customer!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    viewRestaurantsButton = new QPushButton("Browse Restaurants");
    viewCartButton = new QPushButton("View Shopping Cart");
    logoutButton = new QPushButton("Logout");

    layout->addWidget(welcomeLabel);
    layout->addWidget(viewRestaurantsButton);
    layout->addWidget(viewCartButton);
    layout->addWidget(logoutButton);

    connect(viewRestaurantsButton, &QPushButton::clicked, [this]() {
        auto* listWidget = new RestaurantListWidget();
        listWidget->setWindowTitle("Available Restaurants");
        listWidget->resize(400, 400);
        listWidget->show();
    });
    connect(viewCartButton, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Cart", "Coming soon...");
    });

    connect(logoutButton, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Logout", "Logging out...");
        qApp->exit(); // موقت
    });
}
