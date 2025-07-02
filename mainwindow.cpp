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



/*
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Food Delivery System 🍽️");

    // ایجاد منو
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenu = menuBar->addMenu("File");

    QAction* loginAction = new QAction("Login", this);
    QAction* exitAction = new QAction("Exit", this);

    fileMenu->addAction(loginAction);
    fileMenu->addAction(exitAction);

    setMenuBar(menuBar);

    // کانکشن‌ها
    connect(loginAction, &QAction::triggered, this, &MainWindow::onLoginClicked);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClicked);

    // محتوا
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
   QLabel* welcomeLabel = new QLabel("به سامانه سفارش غذای آنلاین خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(welcomeLabel);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

}

*/


#include "MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include "LoginDialog.h"
#include "CustomerService.h"
#include "CustomerPanel.h"
#include "RestaurantOwnerPanel.h"
#include "AdminPanel.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("🍽️ سامانه سفارش غذای آنلاین");

    // نوار منو
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("گزینه‌ها");

    loginAction = new QAction("ورود به سیستم", this);
    exitAction = new QAction("خروج", this);

    fileMenu->addAction(loginAction);
    fileMenu->addAction(exitAction);
    setMenuBar(menuBar);

    // اتصال اکشن‌ها
    connect(loginAction, &QAction::triggered, this, &MainWindow::onLoginClicked);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClicked);

    // متن خوش‌آمدگویی
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    QLabel* welcomeLabel = new QLabel("✨ به سامانه سفارش غذا خوش آمدید");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    mainLayout->addWidget(welcomeLabel);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoginClicked()
{
    LoginDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        auto user = dialog.getLoggedInUser();
        if (!user) {
            QMessageBox::warning(this, "ورود ناموفق", "کاربری وارد نشد.");
            return;
        }

        // CustomerService::instance().setCurrentUser(user);
        CustomerService::instance().setCurrentUser(std::shared_ptr<User>(std::move(user)));
        QWidget* nextPanel = nullptr;
        switch (user->getUserType()) {
        case UserType::CUSTOMER:
            nextPanel = new CustomerPanel();
            break;
        case UserType::RESTAURANT_OWNER:
            nextPanel = new RestaurantOwnerPanel();
            break;
        case UserType::ADMIN:
            nextPanel = new AdminPanel();
            break;
        default:
            QMessageBox::warning(this, "خطا", "نوع کاربر نامشخص است.");
            return;
        }

        if (nextPanel) {
            setCentralWidget(nextPanel);
        }
    }
}

void MainWindow::onExitClicked()
{
    QApplication::quit();
}
