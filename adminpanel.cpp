#include "AdminPanel.h"
#include <QMessageBox>
#include <QApplication>
#include "userlistwidget.h"
#include "orderlistwidget.h"
#include "ClientDatabaseManager.h"
// AdminPanel::AdminPanel(QWidget *parent)
//     : QWidget(parent)
// {
//     setWindowTitle("🛡️ Admin Dashboard");
//     resize(400, 300);

//     titleLabel = new QLabel("🧭 Welcome, Admin!", this);
//     titleLabel->setAlignment(Qt::AlignCenter);
//     titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

//     viewUsersBtn = new QPushButton("👥 View All Users");
//     viewOrdersBtn = new QPushButton("📦 View All Orders");
//     exitBtn = new QPushButton("❌ Exit");

//     layout = new QVBoxLayout(this);
//     layout->addWidget(titleLabel);
//     layout->addSpacing(10);
//     layout->addWidget(viewUsersBtn);
//     layout->addWidget(viewOrdersBtn);
//     layout->addWidget(exitBtn);

//     // اتصال‌ها
//     connect(viewUsersBtn, &QPushButton::clicked, this, &AdminPanel::onViewUsersClicked);
//     connect(viewOrdersBtn, &QPushButton::clicked, this, &AdminPanel::onViewOrdersClicked);
//     connect(exitBtn, &QPushButton::clicked, this, &AdminPanel::onExitClicked);
// }

void AdminPanel::onViewUsersClicked()
{
    auto* widget = new UserListWidget();
    widget->show();
}

void AdminPanel::onViewOrdersClicked()
{
    auto* orders = new OrderListWidget();
    orders->show();
}

void AdminPanel::onExitClicked()
{
    QMessageBox::information(this, "Exit", "👋 Logging out...");
    qApp->exit();
}


AdminPanel::AdminPanel(ClientNetwork* net, QWidget *parent)
    : QWidget(parent), network(net)
{
    setWindowTitle("🛡️ Admin Dashboard");
    resize(400, 300);

    // ساخت لایه
    layout = new QVBoxLayout(this);

    // جدول سفارش‌ها
    ordersTable = new QTableWidget(this);
    ordersTable->setColumnCount(4);
    QStringList headers = {"شناسه", "وضعیت", "جمع کل", "اقلام"};
    ordersTable->setHorizontalHeaderLabels(headers);
    layout->addWidget(ordersTable);

    // اجزای گرافیکی
    titleLabel = new QLabel("🧭 Welcome, Admin!", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(titleLabel);
    layout->addSpacing(10);

    viewUsersBtn = new QPushButton("👥 View All Users");
    viewOrdersBtn = new QPushButton("📦 View All Orders");
    exitBtn = new QPushButton("❌ Exit");

    layout->addWidget(viewUsersBtn);
    layout->addWidget(viewOrdersBtn);
    layout->addWidget(exitBtn);

    // اتصال سیگنال‌ها
    connect(viewUsersBtn, &QPushButton::clicked, this, &AdminPanel::onViewUsersClicked);
    connect(viewOrdersBtn, &QPushButton::clicked, this, &AdminPanel::onViewOrdersClicked);
    connect(exitBtn, &QPushButton::clicked, this, &AdminPanel::onExitClicked);
}




void AdminPanel::refreshOrders()
{
    ordersTable->setRowCount(0);  // پاکسازی جدول

    QList<QMap<QString, QVariant>> orders = ClientDatabaseManager::instance().getAllOrders();
    for (const auto& order : orders) {
        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);

        ordersTable->setItem(row, 0, new QTableWidgetItem(QString::number(order["id"].toInt())));
        ordersTable->setItem(row, 1, new QTableWidgetItem(order["status"].toString()));
        ordersTable->setItem(row, 2, new QTableWidgetItem(QString::number(order["total"].toDouble())));
        ordersTable->setItem(row, 3, new QTableWidgetItem(order["items"].toString()));
    }
}
