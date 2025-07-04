#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "restaurantlistwindow.h"
#include "adminpanel.h"
#include "restaurantownerpanel.h"

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
    QString selectedRole = roleCombo->currentText().trimmed().toLower();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    QString role;
    if (selectedRole == "customer")
        role = "CUSTOMER";
    else if (selectedRole == "restaurant owner")
        role = "RESTAURANT_OWNER";
    else if (selectedRole == "admin")
        role = "ADMIN";
    else
        role = "UNKNOWN";

    QString message = QString("LOGIN|%1|%2|%3").arg(username, password, role);
    network->sendMessage(message);
}

void LoginWindow::onMessageReceived(const QString& msg)
{
    QStringList parts = msg.split("|");
    if (parts.size() >= 3 && parts[0] == "LOGIN_RESULT" && parts[1] == "SUCCESS") {
        QString role = parts[2].trimmed();

        statusLabel->setText("✅ Login successful!");

        if (role.compare("customer", Qt::CaseInsensitive) == 0) {
            auto* customerWin = new RestaurantListWindow(network, this);
            customerWin->setAttribute(Qt::WA_DeleteOnClose);
            customerWin->show();
        } else if (role.compare("restaurant_owner", Qt::CaseInsensitive) == 0 ||
                   role.compare("restaurantowner", Qt::CaseInsensitive) == 0) {
            if (parts.size() >= 4) {
                int restaurantId = parts[3].toInt();
                auto* ownerWin = new RestaurantOwnerPanel(network, restaurantId, this);
                ownerWin->setAttribute(Qt::WA_DeleteOnClose);
                ownerWin->show();
            } else {
                QMessageBox::warning(this, "Invalid data", "Restaurant ID missing for owner login.");
                return;
            }
        } else if (role.compare("admin", Qt::CaseInsensitive) == 0) {
            auto* adminWin = new AdminPanel(network, this);
            adminWin->setAttribute(Qt::WA_DeleteOnClose);
            adminWin->show();
        } else {
            QMessageBox::warning(this, "Unknown role", "Unknown user role received from server.");
            return;
        }

        this->hide(); // پنهان کردن پنجره لاگین
    } else {
        statusLabel->setText("❌ " + msg);
    }
}

void LoginWindow::onNetworkError(const QString& err)
{
    QMessageBox::critical(this, "Network Error", err);
}

QString LoginWindow::getUsername() const {
    return usernameEdit->text().trimmed();
}

QString LoginWindow::getPassword() const {
    return passwordEdit->text().trimmed();
}

QString LoginWindow::getRole() const {
    return roleCombo->currentText().trimmed().toLower();
}
