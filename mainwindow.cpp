#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include "LoginDialog.h"
#include "enums.h"
#include "CustomerPanel.h"
#include "Restaurant.h"

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

MainWindow::~MainWindow() {}

void MainWindow::onLoginClicked() {
    LoginDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        auto user = dialog.getLoggedInUser();
        if (user && user->getUserType() == UserType::CUSTOMER) {
            auto* panel = new CustomerPanel();
            setCentralWidget(panel);
        }
    }
}


void MainWindow::onExitClicked() {
    close();
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QLabel* welcomeLabel = new QLabel("به سامانه سفارش غذای آنلاین خوش آمدید!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    setCentralWidget(centralWidget);
}
