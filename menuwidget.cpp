#include "MenuWidget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>

MenuWidget::MenuWidget(const Restaurant& restaurant, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("🍽️ Menu of " + restaurant.getName());
    title->setAlignment(Qt::AlignCenter);
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

        vbox->addWidget(desc);
        vbox->addWidget(price);
        vbox->addWidget(addBtn);
        box->setLayout(vbox);
        layout->addWidget(box);

        connect(addBtn, &QPushButton::clicked, [=]() {
            emit foodAdded(food);
            QMessageBox::information(this, "Added", food.getName() + " added to cart.");
        });
    }
}
