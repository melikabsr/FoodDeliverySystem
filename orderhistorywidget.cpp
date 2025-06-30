#include "OrderHistoryWidget.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

OrderHistoryWidget::OrderHistoryWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("📜 Order History");

    layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("📦 Your Order History:");
    title->setStyleSheet("font-weight: bold; font-size: 18px;");
    layout->addWidget(title);

    loadOrders();
}

void OrderHistoryWidget::loadOrders()
{
    QString username = CustomerService::instance().getCurrentUsername();
    QVector<Order> orders = OrderManager::instance().getOrdersForCustomer(username);

    if (orders.isEmpty()) {
        QLabel* empty = new QLabel("❌ No orders yet.");
        layout->addWidget(empty);
        return;
    }

    for (const Order& order : orders) {
        QGroupBox* box = new QGroupBox(QString("🧾 Order #%1").arg(order.getId()));
        QVBoxLayout* boxLayout = new QVBoxLayout(box);

        QLabel* status = new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus())));
        QLabel* total = new QLabel(QString("Total: $%1").arg(order.getTotalAmount()));
        boxLayout->addWidget(status);
        boxLayout->addWidget(total);

        for (const auto& pair : order.getItems()) {
            const Food& food = pair.first;
            int qty = pair.second;
            QLabel* itemLabel = new QLabel(QString("🍽️ %1 x %2").arg(food.getName()).arg(qty));
            boxLayout->addWidget(itemLabel);
        }

        layout->addWidget(box);
    }
}
