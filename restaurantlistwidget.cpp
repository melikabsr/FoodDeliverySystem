#include "RestaurantListWidget.h"
#include <QGroupBox>
#include <QMessageBox>
RestaurantListWidget::RestaurantListWidget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    loadRestaurants();
    displayRestaurants();
}

void RestaurantListWidget::loadRestaurants()
{
    mockRestaurants.append(Restaurant(1, "Pizza House", "Main Street 101"));
    mockRestaurants.append(Restaurant(2, "Kebab City", "Vali-Asr Ave 55"));
    mockRestaurants.append(Restaurant(3, "Cafe Queen", "Shahrak Blvd 19"));
}

void RestaurantListWidget::displayRestaurants()
{
    for (const Restaurant& r : mockRestaurants) {
        QGroupBox* card = new QGroupBox(r.getName());
        QVBoxLayout* vbox = new QVBoxLayout(card);

        QLabel* addressLabel = new QLabel("📍 Address: " + r.getAddress());
        QPushButton* viewMenuBtn = new QPushButton("View Menu");

        vbox->addWidget(addressLabel);
        vbox->addWidget(viewMenuBtn);
        card->setLayout(vbox);

        mainLayout->addWidget(card);

        connect(viewMenuBtn, &QPushButton::clicked, [r]() {
            QMessageBox::information(nullptr, "Restaurant", "Menu of: " + r.getName());
        });
    }
}
