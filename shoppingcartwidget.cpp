#include "ShoppingCartWidget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "CustomerService.h"
#include <enums.h>
#include "Order.h"
#include "OrderManager.h"
#include "ClientNetwork.h"



void ShoppingCartWidget::addItem(const Food& food)
{
    int id = food.getId();
    if (items.contains(id)) {
        auto pair = items.value(id);
        pair.second += 1;
        items.insert(id, pair);
    } else {
        items.insert(id, qMakePair(food, 1));
    }

    updateDisplay();
}

void ShoppingCartWidget::removeItem(int id)
{
    if (items.contains(id)) {
        items.remove(id);
        updateDisplay();
    }
}

void ShoppingCartWidget::updateDisplay()
{
    QLayoutItem *item;
    while ((item = layout->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }

    double total = 0;

    for (auto it = items.begin(); it != items.end(); ++it) {
        const Food& food = it.value().first;
        int qty = it.value().second;
        double price = food.getPrice() * qty;

        QGroupBox* box = new QGroupBox(food.getName());
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QLabel* desc = new QLabel(food.getDescription());
        QLabel* priceLabel = new QLabel(QString("💰 %1 × %2 = %3 $").arg(food.getPrice()).arg(qty).arg(price));
        QPushButton* removeBtn = new QPushButton("🗑 Remove");

        connect(removeBtn, &QPushButton::clicked, [=]() {
            removeItem(food.getId());
        });

        vbox->addWidget(desc);
        vbox->addWidget(priceLabel);
        vbox->addWidget(removeBtn);
        layout->addWidget(box);

        total += price;
    }

    totalLabel->setText(QString("Total: $%1").arg(total));
}

void ShoppingCartWidget::refresh()
{
    QLayoutItem* item;
    while ((item = layout->takeAt(1)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    layout->insertWidget(0, totalLabel);
    loadCartItems();
}

void ShoppingCartWidget::loadCartItems()
{
    double total = 0;
    auto cartItems = CustomerService::instance().getCartItems();

    for (const auto& pair : cartItems) {
        const Food& food = pair.first;
        int qty = pair.second;
        double price = food.getPrice() * qty;
        total += price;

        QGroupBox* box = new QGroupBox(food.getName());
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QLabel* info = new QLabel(QString("📝 %1\n💵 %2 × %3 = %4 $")
                                      .arg(food.getDescription())
                                      .arg(food.getPrice())
                                      .arg(qty)
                                      .arg(price));

        QPushButton* removeBtn = new QPushButton("🗑 Remove");

        connect(removeBtn, &QPushButton::clicked, [=]() {
            CustomerService::instance().removeItem(food.getId());
            refresh();
        });

        vbox->addWidget(info);
        vbox->addWidget(removeBtn);
        box->setLayout(vbox);
        layout->addWidget(box);
    }

    totalLabel->setText(QString("Total: $%1").arg(total));
}





ShoppingCartWidget::ShoppingCartWidget(ClientNetwork* network, const QString& username, QWidget* parent)
    : QWidget(parent), network(network), username(username)
{
    setWindowTitle("🛒 Your Cart - " + username);
    resize(450, 500);

    layout = new QVBoxLayout(this);
    totalLabel = new QLabel("Total: $0", this);
    totalLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(totalLabel);

    loadCartItems();

    QPushButton* clearBtn = new QPushButton("❌ Clear Cart");
    QPushButton* checkoutBtn = new QPushButton("✅ Submit Order");
    layout->addWidget(clearBtn);
    layout->addWidget(checkoutBtn);

    connect(clearBtn, &QPushButton::clicked, [=]() {
        CustomerService::instance().clearCart();
        refresh();
    });

    connect(checkoutBtn, &QPushButton::clicked, [=]() {
        auto items = CustomerService::instance().getCartItems();
        if (items.isEmpty()) {
            QMessageBox::warning(this, "Cart Empty", "Your cart is empty.");
            return;
        }

        Order newOrder(OrderManager::instance().getAllOrders().size() + 1, username);
        for (const auto& pair : items) {
            const Food& food = pair.first;
            int qty = pair.second;
            newOrder.addItem(food, qty);
        }

        OrderManager::instance().addOrder(newOrder);
        QMessageBox::information(this, "Success", "Order submitted successfully!");

        CustomerService::instance().clearCart();
        refresh();
    });
}
