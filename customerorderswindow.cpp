#include "CustomerOrdersWindow.h"
#include <QLabel>
#include <QGroupBox>
#include <QDebug>

CustomerOrdersWindow::CustomerOrdersWindow(const QString& username, ClientNetwork* network, QWidget* parent)
    : QWidget(parent), customerUsername(username), clientNetwork(network)
{
    setWindowTitle("📦 My Orders");
    resize(600, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);
    scrollArea = new QScrollArea(this);
    QWidget* container = new QWidget();
    mainLayout = new QVBoxLayout(container);

    container->setLayout(mainLayout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);

    layout->addWidget(scrollArea);
    setLayout(layout);

    // اتصال سیگنال پیام دریافتی
    connect(clientNetwork, &ClientNetwork::messageReceived, this, &CustomerOrdersWindow::handleOrderResponse);

    // درخواست سفارش‌ها از سرور
    QString request = "GET_ORDERS|" + customerUsername;
    clientNetwork->sendMessage(request);
}

void CustomerOrdersWindow::handleOrderResponse(const QString& message)
{
    if (!message.startsWith("ORDERS|")) return;

    QString data = message.mid(QString("ORDERS|").length());
    QStringList orderList = data.split(";", Qt::SkipEmptyParts);

    // پاک‌سازی قبلی
    QLayoutItem* item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (orderList.isEmpty()) {
        mainLayout->addWidget(new QLabel("❌ No orders found."));
        return;
    }

    for (const QString& orderStr : orderList) {
        QGroupBox* box = new QGroupBox(orderStr);
        box->setStyleSheet("font-weight: bold;");
        mainLayout->addWidget(box);
    }
}
