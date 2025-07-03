// OrdersWindow.cpp
#include "OrdersWindow.h"
#include "ClientDatabaseManager.h"

OrdersWindow::OrdersWindow(QWidget* parent)
    : QWidget(parent)
{
    orderList = new QListWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(orderList);
    setLayout(layout);
}

void OrdersWindow::refreshOrders()
{
    orderList->clear();

    QList<QMap<QString, QVariant>> orders = ClientDatabaseManager::instance().getAllOrders();

    for (const auto& order : orders) {
        QString line = QString("🧾 سفارش #%1 - %2 تومان - [%3]")
                           .arg(order["id"].toInt())
                           .arg(order["total"].toDouble())
                           .arg(order["items"].toString());
        orderList->addItem(line);
    }
}
