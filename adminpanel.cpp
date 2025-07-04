#include "AdminPanel.h"
#include <QMessageBox>
#include <QHeaderView>

AdminPanel::AdminPanel(ClientNetwork* net, QWidget *parent)
    : QWidget(parent), network(net)
{
    setWindowTitle("🛡️ Admin Dashboard");
    resize(600, 500);

    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("👑 Welcome, Admin!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(titleLabel);

    viewUsersBtn = new QPushButton("👥 View All Users");
    viewOrdersBtn = new QPushButton("📦 View All Orders");
    exitBtn = new QPushButton("❌ Exit");

    layout->addWidget(viewUsersBtn);
    layout->addWidget(viewOrdersBtn);
    layout->addWidget(exitBtn);

    ordersTable = new QTableWidget(this);
    ordersTable->setColumnCount(3);
    ordersTable->setHorizontalHeaderLabels({"Order ID", "Username", "Status"});
    ordersTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(ordersTable);
    ordersTable->hide();

    connect(viewUsersBtn, &QPushButton::clicked, this, &AdminPanel::onViewUsersClicked);
    connect(viewOrdersBtn, &QPushButton::clicked, this, &AdminPanel::onViewOrdersClicked);
    connect(exitBtn, &QPushButton::clicked, this, &AdminPanel::onExitClicked);
    connect(network, &ClientNetwork::messageReceived, this, &AdminPanel::onMessageReceived);
}

void AdminPanel::onViewUsersClicked()
{
    network->sendMessage("GET_ALL_USERS");
}

void AdminPanel::onViewOrdersClicked()
{
    network->sendMessage("GET_ALL_ORDERS");
    ordersTable->show();
}

void AdminPanel::onExitClicked()
{
    QMessageBox::information(this, "Logout", "Exiting admin panel...");
    close();
}

void AdminPanel::onMessageReceived(const QString& msg)
{
    if (msg.startsWith("ALL_USERS|")) {
        QStringList users = msg.section("|", 1).split(";", Qt::SkipEmptyParts);
        QString userText = "📋 Registered Users:\n\n" + users.join("\n");
        QMessageBox::information(this, "Users", userText);
    }
    else if (msg.startsWith("ALL_ORDERS|")) {
        QStringList entries = msg.section("|", 1).split(";", Qt::SkipEmptyParts);
        ordersTable->setRowCount(0);

        for (const QString& row : entries) {
            QStringList parts = row.split("|");
            if (parts.size() < 3) continue;

            int r = ordersTable->rowCount();
            ordersTable->insertRow(r);
            ordersTable->setItem(r, 0, new QTableWidgetItem(parts[0].trimmed()));
            ordersTable->setItem(r, 1, new QTableWidgetItem(parts[1].trimmed()));
            ordersTable->setItem(r, 2, new QTableWidgetItem(parts[2].trimmed()));
        }
    }
}
