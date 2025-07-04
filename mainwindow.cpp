#include "MainWindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("🍽️ سامانه سفارش غذای آنلاین");

    network = new ClientNetwork(this);
    if (!network->connectToServer("127.0.0.1", 1234)) {
        QMessageBox::critical(this, "اتصال ناموفق", "ارتباط با سرور برقرار نشد.");
    }

    connect(network, &ClientNetwork::messageReceived,
            this, &MainWindow::onMessageReceived);

    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("File");

    loginAction = new QAction("Login", this);
    exitAction = new QAction("Exit", this);

    fileMenu->addAction(loginAction);
    fileMenu->addAction(exitAction);
    setMenuBar(menuBar);

    connect(loginAction, &QAction::triggered, this, &MainWindow::onLoginClicked);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClicked);

    showWelcomeScreen();
}

MainWindow::~MainWindow() {}

void MainWindow::showWelcomeScreen()
{
    QWidget* welcomeWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(welcomeWidget);

    QLabel* welcomeLabel = new QLabel("👋 به سامانه سفارش غذا خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    statusLabel = new QLabel("لطفاً از منوی بالا وارد شوید.");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: gray;");
    layout->addWidget(statusLabel);

    welcomeWidget->setLayout(layout);
    setCentralWidget(welcomeWidget);
}

void MainWindow::onLoginClicked()
{
    LoginDialog loginDialog(network, this);
    if (loginDialog.exec() == QDialog::Accepted) {
        username = loginDialog.getUsername();
        userRole = loginDialog.getRole();
        statusLabel->setText("⏳ در حال ورود...");
    }
}

void MainWindow::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("LOGIN_RESULT|")) return;

    QStringList parts = msg.split("|");
    if (parts.size() < 3) {
        statusLabel->setText("❌ پاسخ نامعتبر از سرور.");
        return;
    }

    QString result = parts[1];
    QString role = parts[2].toUpper();

    if (result != "SUCCESS") {
        statusLabel->setText("❌ ورود ناموفق: " + msg);
        return;
    }

    if (role == "CUSTOMER") {
        auto* panel = new CustomerPanel(network, username);
        connect(network, &ClientNetwork::ordersUpdated,
                panel, &CustomerPanel::refreshOrders);
        setCentralWidget(panel);
    }
    else if (role == "RESTAURANT_OWNER") {
        if (parts.size() >= 4) {
            int restaurantId = parts[3].toInt();
            auto* panel = new RestaurantOwnerPanel(network, restaurantId);
            connect(network, &ClientNetwork::ordersUpdated,
                    panel, &RestaurantOwnerPanel::refreshOrders);
            setCentralWidget(panel);
        } else {
            QMessageBox::warning(this, "Login Error", "Restaurant ID not received from server.");
        }
    }
    else if (role == "ADMIN") {
        auto* panel = new AdminPanel(network);
        setCentralWidget(panel);
    }
    else {
        QMessageBox::warning(this, "Login Error", "Unknown role: " + role);
    }
}

void MainWindow::onExitClicked()
{
    qApp->quit();
}
