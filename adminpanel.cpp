#include "AdminPanel.h"
#include <QMessageBox>
#include <QApplication>

AdminPanel::AdminPanel(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("🛡️ Admin Dashboard");
    resize(400, 300);

    titleLabel = new QLabel("🧭 Welcome, Admin!", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    viewUsersBtn = new QPushButton("👥 View All Users");
    viewOrdersBtn = new QPushButton("📦 View All Orders");
    exitBtn = new QPushButton("❌ Exit");

    layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(viewUsersBtn);
    layout->addWidget(viewOrdersBtn);
    layout->addWidget(exitBtn);

    connect(viewUsersBtn, &QPushButton::clicked, this, &AdminPanel::onViewUsersClicked);
    connect(viewOrdersBtn, &QPushButton::clicked, this, &AdminPanel::onViewOrdersClicked);
    connect(exitBtn, &QPushButton::clicked, this, &AdminPanel::onExitClicked);
}

void AdminPanel::onViewUsersClicked()
{
    QMessageBox::information(this, "Users", "📋 User list will be shown here.");
}

void AdminPanel::onViewOrdersClicked()
{
    QMessageBox::information(this, "Orders", "📦 Order list will be shown here.");
}

void AdminPanel::onExitClicked()
{
    QMessageBox::information(this, "Exit", "👋 Logging out...");
    qApp->exit();  // برای بستن کل برنامه
}
