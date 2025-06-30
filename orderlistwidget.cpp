#include "orderlistwidget.h"
#include "OrderManager.h"
#include "Order.h"
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

OrderListWidget::OrderListWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("📦 All Orders in System");
    resize(550, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("📋 لیست سفارش‌های ثبت‌شده:");
    title->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(title);

    const auto& orders = OrderManager::instance().getAllOrders();
    if (orders.isEmpty()) {
        layout->addWidget(new QLabel("❌ هیچ سفارشی وجود ندارد."));
        return;
    }

    for (const auto& order : orders) {
        QGroupBox* box = new QGroupBox(
            QString("🧾 Order #%1 | Customer: %2")
                .arg(order.getId())
                .arg(order.getCustomerUsername())
            );

        QVBoxLayout* boxLayout = new QVBoxLayout(box);

        boxLayout->addWidget(new QLabel(QString("Total Items: %1").arg(order.getItems().size())));
        boxLayout->addWidget(new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus()))));
        boxLayout->addWidget(new QLabel(QString("Total Amount: $%1").arg(order.getTotalAmount())));

        // لیست غذاها
        for (const auto& pair : order.getItems()) {
            const Food& food = pair.first;
            int qty = pair.second;
            QLabel* itemLabel = new QLabel(QString("🍽️ %1 × %2").arg(food.getName()).arg(qty));
            boxLayout->addWidget(itemLabel);
        }

        QPushButton* removeBtn = new QPushButton("❌ Remove");
        connect(removeBtn, &QPushButton::clicked, [=]() {
            OrderManager::instance().removeOrder(order.getId());
            box->hide();
            QMessageBox::information(this, "Removed", "Order deleted.");
        });

        boxLayout->addWidget(removeBtn);
        box->setLayout(boxLayout);
        layout->addWidget(box);
    }
}
