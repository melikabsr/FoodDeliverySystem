#include "MenuWidget.h"
#include "CustomerService.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>

MenuWidget::MenuWidget(const Restaurant& restaurant, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("🍽️ Menu of " + restaurant.getName());
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-weight: bold; font-size: 18px; margin: 10px;");
    layout->addWidget(title);

    loadMenu(restaurant.getMenu());
}

void MenuWidget::loadMenu(const QList<Food>& menu)
{
    for (const Food& food : menu) {
        QGroupBox* box = new QGroupBox(food.getName());
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QLabel* desc = new QLabel("📝 " + food.getDescription());
        QLabel* price = new QLabel(QString("💵 %1 $").arg(food.getPrice()));
        QPushButton* addBtn = new QPushButton("➕ Add to Cart");

        desc->setStyleSheet("color: #444;");
        price->setStyleSheet("color: green; font-weight: bold;");

        vbox->addWidget(desc);
        vbox->addWidget(price);
        vbox->addWidget(addBtn);
        box->setLayout(vbox);

        layout->addWidget(box);

        connect(addBtn, &QPushButton::clicked, [=]() {
            CustomerService::instance().addToCart(food);
            QMessageBox::information(this, "Added", food.getName() + " added to cart.");
            emit foodAdded(food);
        });
    }
}
