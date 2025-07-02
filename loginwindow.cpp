#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "restaurantlistwindow.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("🔐 Login");
    resize(300, 200);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    roleCombo = new QComboBox(this);
    loginButton = new QPushButton("Login", this);
    statusLabel = new QLabel(this);

    passwordEdit->setEchoMode(QLineEdit::Password);
    roleCombo->addItem("Customer");
    roleCombo->addItem("Restaurant Owner");
    roleCombo->addItem("Admin");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Username:"));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(passwordEdit);
    layout->addWidget(new QLabel("Role:"));
    layout->addWidget(roleCombo);
    layout->addWidget(loginButton);
    layout->addWidget(statusLabel);

    network = new ClientNetwork(this);
    connect(network, &ClientNetwork::messageReceived, this, &LoginWindow::onMessageReceived);
    connect(network, &ClientNetwork::errorOccurred, this, &LoginWindow::onNetworkError);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);

    if (!network->connectToServer("127.0.0.1", 1234)) {
        statusLabel->setText("❌ Could not connect to server.");
    } else {
        statusLabel->setText("✅ Connected to server.");
    }
}

void LoginWindow::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    QString message = QString("LOGIN|%1|%2").arg(username, password);
    network->sendMessage(message);
}

void LoginWindow::onMessageReceived(const QString& msg)
{
    if (msg.startsWith("✅ LOGIN")) {
        statusLabel->setText("✅ Login successful!");

        auto* listWindow = new RestaurantListWindow(network);  // ارسال pointer شبکه
        listWindow->show();
        this->close();
    } else {
        statusLabel->setText("❌ " + msg);
    }
}

void LoginWindow::onNetworkError(const QString& err)
{
    statusLabel->setText("⚠️ " + err);
}
