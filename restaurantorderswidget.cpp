#include "RestaurantOrdersWidget.h"
#include "OrderStatusEditor.h"
#include "ClientNetwork.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

RestaurantOrdersWidget::RestaurantOrdersWidget(ClientNetwork* net, int restaurantId, QWidget* parent)
    : QWidget(parent), network(net), rId(restaurantId)
{
    setWindowTitle("📦 Manage Orders");
    resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);
    orderList = new QListWidget(this);
    refreshBtn = new QPushButton("🔄 Refresh Orders");
    changeStatusBtn = new QPushButton("✏️ Change Status");

    layout->addWidget(orderList);
    layout->addWidget(refreshBtn);
    layout->addWidget(changeStatusBtn);

    connect(refreshBtn, &QPushButton::clicked, this, &RestaurantOrdersWidget::refreshOrders);
    connect(changeStatusBtn, &QPushButton::clicked, this, &RestaurantOrdersWidget::onStatusChangeClicked);
    connect(network, &ClientNetwork::messageReceived, this, &RestaurantOrdersWidget::onMessageReceived);

    refreshOrders();
}

void RestaurantOrdersWidget::refreshOrders()
{
    QString msg = QString("GET_ORDERS_BY_RESTAURANT|%1").arg(rId);
    network->sendMessage(msg);
}
/*
void RestaurantOrdersWidget::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("RESTAURANT_ORDERS|"))
        return;

    orderList->clear();
    itemToOrderId.clear();

    QStringList rows = msg.section("|", 1).split(";");
    for (const QString& row : rows) {
        QStringList parts = row.split("|");
        if (parts.size() < 4) continue;

        int orderId = parts[0].toInt();
        QString customer = parts[1];
        QString status = parts[2];
        QString itemsStr = parts[3];

        QString displayText = QString("🧾 #%1 - %2 [%3]").arg(orderId).arg(customer).arg(status);
        QListWidgetItem* item = new QListWidgetItem(displayText);
        orderList->addItem(item);
        itemToOrderId[item] = orderId;
    }


    // بررسی پیام پاسخ به بروزرسانی وضعیت سفارش
    if (msg.startsWith("STATUS_UPDATED|")) {
        QMessageBox::information(this, "✅ Success", "Order status updated successfully.");
        refreshOrders();
    }
    else if (msg.startsWith("ERROR_STATUS_UPDATE|")) {
        QString reason = msg.section("|", 1);
        QMessageBox::critical(this, "❌ Update Failed", "Could not update status: " + reason);
    }

}
*/
void RestaurantOrdersWidget::onStatusChangeClicked()
{
    auto* item = orderList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "❗ No Selection", "Please select an order to update.");
        return;
    }

    int orderId = itemToOrderId.value(item, -1);
    if (orderId == -1) {
        QMessageBox::warning(this, "❌ Error", "Invalid order selected.");
        return;
    }

    auto* editor = new OrderStatusEditor(orderId, network, this);
    editor->setAttribute(Qt::WA_DeleteOnClose);  // ویجت پس از بسته شدن حذف می‌شود
    editor->show();
}





void RestaurantOrdersWidget::onMessageReceived(const QString& msg)
{
    if (msg.startsWith("RESTAURANT_ORDERS|")) {
        orderList->clear();
        itemToOrderId.clear();

        QStringList rows = msg.section("|", 1).split(";");
        for (const QString& row : rows) {
            QStringList parts = row.split("|");
            if (parts.size() < 4) continue;

            int orderId = parts[0].toInt();
            QString customer = parts[1];
            QString status = parts[2];
            QString itemsStr = parts[3];

            QListWidgetItem* item = new QListWidgetItem(
                QString("🧾 #%1 - %2 [%3]").arg(orderId).arg(customer).arg(status)
                );
            orderList->addItem(item);
            itemToOrderId[item] = orderId;
        }
    }

    else if (msg.startsWith("STATUS_UPDATED|OK")) {
        QMessageBox::information(this, "Success", "✅ وضعیت سفارش با موفقیت به‌روزرسانی شد.");
        refreshOrders(); // برای بارگذاری مجدد وضعیت جدید
    }

    else if (msg.startsWith("ERROR_STATUS_UPDATE|")) {
        QString err = msg.section("|", 1);
        QMessageBox::critical(this, "Error", "❌ خطا در به‌روزرسانی: " + err);
    }
}
