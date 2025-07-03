#include <QDebug>
#include <QMessageBox>
#include "LoginDialog.h"
#include "enums.h"
#include "CustomerPanel.h"
#include "Restaurant.h"
#include "MenuWidget.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <memory>
#include "CustomerService.h"
#include "RestaurantOwnerPanel.h"
#include "AdminPanel.h"
#include <QApplication>


#include <QDebug>
#include <QMessageBox>
#include "LoginDialog.h"
#include "CustomerPanel.h"
#include "MainWindow.h"
#include "ClientNetwork.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("سامانه سفارش غذای آنلاین");

    // ساخت اتصال شبکه
    network = new ClientNetwork(this);
    if (!network->connectToServer("127.0.0.1", 1234)) {
        QMessageBox::critical(this, "اتصال ناموفق", "ارتباط با سرور برقرار نشد.");
    }

    // نوار منو
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("File");

    loginAction = new QAction("Login", this);
    exitAction = new QAction("Exit", this);

    fileMenu->addAction(loginAction);
    fileMenu->addAction(exitAction);
    setMenuBar(menuBar);

    connect(loginAction, &QAction::triggered, this, &MainWindow::onLoginClicked);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClicked);

    // ایجاد ویجت مرکزی و تنظیم آن
    QWidget* mainWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(mainWidget);

    QLabel* welcomeLabel = new QLabel("به سامانه سفارش غذای آنلاین خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    layout->addWidget(statusLabel);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow() {}
void MainWindow::onMessageReceived(const QString& msg)
{
    QStringList parts = msg.split("|");
    if (parts.size() >= 3 && parts[0] == "LOGIN_RESULT" && parts[1] == "SUCCESS") {
        QString role = parts[2].trimmed().toUpper();
        statusLabel->setText("✅ Login successful!");

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
                QMessageBox::warning(this, "Login Error", "Restaurant ID not provided by server.");
            }
        }

        else {
            QMessageBox::warning(this, "Login Error", "Unknown role received from server.");
        }

    }
    else {
        statusLabel->setText("❌ " + msg);
    }
}


void MainWindow::onExitClicked()
{
    qApp->quit();
}


void MainWindow::showWelcomeScreen()
{
    // حذف ویجت قبلی برای جلوگیری از memory leak
    QWidget* oldWidget = centralWidget();
    if (oldWidget)
        oldWidget->deleteLater();

    QWidget* welcomeWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(welcomeWidget);

    QLabel* welcomeLabel = new QLabel("به سامانه سفارش غذای آنلاین خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    layout->addWidget(statusLabel);

    welcomeWidget->setLayout(layout);
    setCentralWidget(welcomeWidget);
}


void MainWindow::onLoginClicked()
{
    LoginDialog loginDialog(network, this);  // ✅ درست
     // فرض بر اینکه network از قبل ساخته شده
    if (loginDialog.exec() == QDialog::Accepted) {
        username = loginDialog.getUsername();  // ✅ اینجا ذخیره کن
        QString password = loginDialog.getPassword();
        QString role = loginDialog.getRole();

        connect(network, &ClientNetwork::messageReceived,
                this, &MainWindow::onMessageReceived);

        network->sendMessage(QString("LOGIN|%1|%2|%3").arg(username, password, role));
    }
}
