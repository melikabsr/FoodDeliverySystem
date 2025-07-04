#include "RestaurantOrdersWindow.h"
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>

RestaurantOrdersWindow::RestaurantOrdersWindow(int restaurantId, ClientNetwork* network, QWidget* parent)
    : QWidget(parent), restaurantId(restaurantId), clientNetwork(network)
{
    setWindowTitle("📦 Restaurant Orders");
    resize(600, 550);

    QVBoxLayout* layout = new QVBoxLayout(this);
    scrollArea = new QScrollArea(this);
    QWidget* container = new QWidget();
    mainLayout = new QVBoxLayout(container);

    container->setLayout(mainLayout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);

    layout->addWidget(scrollArea);
    setLayout(layout);

    connect(clientNetwork, &ClientNetwork::messageReceived, this, &RestaurantOrdersWindow::handleOrderResponse);

    requestOrders();
}

void RestaurantOrdersWindow::requestOrders()
{
    QString request = "GET_ORDERS_BY_RESTAURANT|" + QString::number(restaurantId);
    clientNetwork->sendMessage(request);
}

void RestaurantOrdersWindow::handleOrderResponse(const QString& message)
{
    if (!message.startsWith("RESTAURANT_ORDERS|")) return;

    QString data = message.section("|", 1);  // همه داده‌ها بعد از اولین '|'
    QStringList orderList = data.split(";", Qt::SkipEmptyParts);

    // پاکسازی سفارش‌های قبلی
    QLayoutItem* item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (orderList.isEmpty()) {
        mainLayout->addWidget(new QLabel("❌ No orders for your restaurant."));
        return;
    }

    for (const QString& row : orderList) {
        QStringList parts = row.split("|");
        if (parts.size() < 4) continue;

        int orderId = parts[0].toInt();
        QString customer = parts[1];
        QString status = parts[2];
        QString items = parts[3];

        QString display = QString("🧾 Order #%1 - %2 - [%3]").arg(orderId).arg(customer).arg(items);
        QGroupBox* box = new QGroupBox(display);
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QComboBox* statusBox = new QComboBox();
        statusBox->addItems({"PENDING", "CONFIRMED", "PREPARING", "READY", "DELIVERED", "CANCELLED"});
        int index = statusBox->findText(status.toUpper());
        if (index >= 0) statusBox->setCurrentIndex(index);

        QPushButton* updateBtn = new QPushButton("Update Status");
        connect(updateBtn, &QPushButton::clicked, this, [=]() {
            updateOrderStatus(orderId, statusBox->currentText());
        });

        vbox->addWidget(statusBox);
        vbox->addWidget(updateBtn);
        box->setLayout(vbox);
        mainLayout->addWidget(box);
    }
}

void RestaurantOrdersWindow::updateOrderStatus(int orderId, const QString& newStatus)
{
    QString msg = QString("UPDATE_ORDER_STATUS|%1|%2").arg(orderId).arg(newStatus);
    clientNetwork->sendMessage(msg);
}
