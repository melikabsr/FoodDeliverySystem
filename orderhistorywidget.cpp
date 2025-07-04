#include "OrderHistoryWidget.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include "ClientDatabaseManager.h"

OrderHistoryWidget::OrderHistoryWidget(ClientNetwork* net, const QString& username, QWidget *parent)
    : QWidget(parent), network(net), username(username)
{
    setWindowTitle("📜 Your Order History");
    resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    orderList = new QListWidget(this);
    refreshBtn = new QPushButton("🔄 Refresh", this);

    layout->addWidget(new QLabel("📋 لیست سفارش‌های شما:", this));
    layout->addWidget(orderList);
    layout->addWidget(refreshBtn);

    connect(refreshBtn, &QPushButton::clicked, this, &OrderHistoryWidget::refreshOrders);
    connect(network, &ClientNetwork::messageReceived, this, &OrderHistoryWidget::onMessageReceived);

    refreshOrders();
}

// درخواست لیست سفارش‌ها از سرور
void OrderHistoryWidget::refreshOrders()
{
    QString msg = QString("GET_ORDERS|%1").arg(username);
    network->sendMessage(msg);
}

// دریافت پاسخ و نمایش سفارش‌ها
void OrderHistoryWidget::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("ORDERS|"))
        return;

    orderList->clear();
    QString data = msg.section("|", 1);
    QStringList orders = data.split(";");

    for (const QString& order : orders) {
        QListWidgetItem* item = new QListWidgetItem(order, orderList);
        if (order.contains("DELIVERED")) {
            item->setBackground(Qt::green);
        } else if (order.contains("READY")) {
            item->setBackground(Qt::yellow);
        } else if (order.contains("PREPARING")) {
            item->setBackground(Qt::lightGray);
        } else if (order.contains("CONFIRMED")) {
            item->setBackground(Qt::cyan);
        } else {
            item->setBackground(Qt::white);
        }
    }
}






OrderHistoryWidget::OrderHistoryWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);

    loadOrders();
}

void OrderHistoryWidget::loadOrders()
{
    QList<QMap<QString, QVariant>> orders = ClientDatabaseManager::instance().getAllOrders();

    for (const auto& order : orders) {
        QString summary = QString("🧾 Order #%1\nStatus: %2\nTotal: %3 تومان\nItems: %4\n")
                              .arg(order["id"].toInt())
                              .arg(order["status"].toString())
                              .arg(order["total"].toDouble())
                              .arg(order["items"].toString());
        listWidget->addItem(summary);
    }
}
