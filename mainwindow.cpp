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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("سامانه سفارش غذای آنلاین");

    // Menu Bar
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("File");

    loginAction = new QAction("Login", this);
    exitAction = new QAction("Exit", this);

    fileMenu->addAction(loginAction);
    fileMenu->addAction(exitAction);

    setMenuBar(menuBar);

    connect(loginAction, &QAction::triggered, this, &MainWindow::onLoginClicked);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClicked);

    // Welcome Text
    centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QLabel* welcomeLabel = new QLabel("به سامانه سفارش غذای آنلاین خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}






MainWindow::~MainWindow() {}

void MainWindow::onLoginClicked() {
    LoginDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        auto user = dialog.getLoggedInUser();
        if (!user) return;

        std::shared_ptr<User> sharedUser = std::move(user);
        CustomerService::instance().setCurrentUser(sharedUser);

        UserType type = sharedUser->getUserType();
        QWidget* panel = nullptr;

        if (type == UserType::CUSTOMER) {
            panel = new CustomerPanel();
        } else if (type == UserType::RESTAURANT_OWNER) {
            panel = new RestaurantOwnerPanel();
        } else if (type == UserType::ADMIN) {
            panel = new AdminPanel();
        }

        if (panel) {
            setCentralWidget(panel);
        }
    }
}


void MainWindow::onExitClicked() {
    close();
}

