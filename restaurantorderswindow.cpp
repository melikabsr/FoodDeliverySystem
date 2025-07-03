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
    if (!message.startsWith("ORDERS|")) return;

    QString data = message.mid(QString("ORDERS|").length());
    QStringList orderList = data.split(";", Qt::SkipEmptyParts);

    QLayoutItem* item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (orderList.isEmpty()) {
        mainLayout->addWidget(new QLabel("❌ No orders for your restaurant."));
        return;
    }

    for (const QString& orderStr : orderList) {
        // فرمت: 🧾 Order #2 - username - 40000 تومان [Pizza×1, Salad×1]
        QString line = orderStr.trimmed();
        QGroupBox* box = new QGroupBox(line);
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QComboBox* statusBox = new QComboBox();
        statusBox->addItems({"PENDING", "CONFIRMED", "PREPARING", "READY", "DELIVERED", "CANCELLED"});

        // استخراج ID سفارش از متن (مثلاً "#2")
        int idStart = line.indexOf("#") + 1;
        int idEnd = line.indexOf(" ", idStart);
        int orderId = line.mid(idStart, idEnd - idStart).toInt();

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
