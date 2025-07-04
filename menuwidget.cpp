#include "MenuWidget.h"
#include "CustomerService.h"
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

MenuWidget::MenuWidget(const QString& restaurantName, const QList<Food>& menu, QWidget* parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("🍽️ Menu of " + restaurantName);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-weight: bold; font-size: 18px; margin: 10px;");
    layout->addWidget(title);

    loadMenu(menu);
}

void MenuWidget::loadMenu(const QList<Food>& menu)
{
    for (const Food& food : menu) {
        QGroupBox* box = new QGroupBox(food.getName());
        box->setStyleSheet("QGroupBox { font-size: 15px; font-weight: bold; }");

        QVBoxLayout* vbox = new QVBoxLayout(box);

        QLabel* desc = new QLabel("📝 " + food.getDescription());
        QLabel* price = new QLabel(QString("💵 %1 $").arg(food.getPrice()));

        desc->setStyleSheet("color: #444;");
        price->setStyleSheet("color: green; font-weight: bold;");

        QHBoxLayout* buttonLayout = new QHBoxLayout();

        QPushButton* addBtn = new QPushButton("➕");
        QPushButton* removeBtn = new QPushButton("➖");

        QLabel* qtyLabel = new QLabel("0");
        qtyLabel->setStyleSheet("font-size: 16px; min-width: 30px; text-align: center;");
        qtyLabel->setAlignment(Qt::AlignCenter);

        quantityLabels[food.getId()] = qtyLabel;

        buttonLayout->addWidget(removeBtn);
        buttonLayout->addWidget(qtyLabel);
        buttonLayout->addWidget(addBtn);

        vbox->addWidget(desc);
        vbox->addWidget(price);
        vbox->addLayout(buttonLayout);
        box->setLayout(vbox);

        layout->addWidget(box);

        connect(addBtn, &QPushButton::clicked, this, [=]() {
            CustomerService::instance().addToCart(food);
            int qty = CustomerService::instance().getQuantity(food);
            updateQuantityLabel(food.getId(), qty);
            emit foodAdded(food);
        });

        connect(removeBtn, &QPushButton::clicked, this, [=]() {
            CustomerService::instance().removeFromCart(food);
            int qty = CustomerService::instance().getQuantity(food);
            updateQuantityLabel(food.getId(), qty);
            emit foodRemoved(food);
        });
    }
}

void MenuWidget::updateQuantityLabel(int foodId, int quantity)
{
    if (quantityLabels.contains(foodId)) {
        quantityLabels[foodId]->setText(QString::number(quantity));
    }
}



