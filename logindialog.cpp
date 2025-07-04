#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginDialog::LoginDialog(ClientNetwork* network, QWidget* parent)
    : QDialog(parent), network(network)
{
    setWindowTitle("🔐 Login");
    resize(300, 220);

    QVBoxLayout* layout = new QVBoxLayout(this);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    roleCombo = new QComboBox(this);
    roleCombo->addItem("Customer");
    roleCombo->addItem("Restaurant Owner");
    roleCombo->addItem("Admin");

    loginButton = new QPushButton("✅ Login", this);

    layout->addWidget(new QLabel("Username:", this));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("Password:", this));
    layout->addWidget(passwordEdit);
    layout->addWidget(new QLabel("Role:", this));
    layout->addWidget(roleCombo);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(network, &ClientNetwork::messageReceived, this, &LoginDialog::onMessageReceived);
}

QString LoginDialog::getUsername() const {
    return usernameEdit->text().trimmed();
}

QString LoginDialog::getPassword() const {
    return passwordEdit->text().trimmed();
}

QString LoginDialog::getRole() const {
    return userRole;
}

void LoginDialog::onLoginClicked()
{
    QString username = getUsername();
    QString password = getPassword();
    QString selected = roleCombo->currentText().toLower();

    QString role;
    if (selected == "customer") role = "CUSTOMER";
    else if (selected == "restaurant owner") role = "RESTAURANT_OWNER";
    else if (selected == "admin") role = "ADMIN";

    userRole = role;

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter username and password.");
        return;
    }

    QString message = QString("LOGIN|%1|%2|%3").arg(username, password, role);
    network->sendMessage(message);
    loginButton->setEnabled(false);
}

void LoginDialog::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("LOGIN_RESULT|")) return;

    loginButton->setEnabled(true);

    QStringList parts = msg.split("|");
    if (parts.size() < 3 || parts[1] != "SUCCESS") {
        QMessageBox::critical(this, "Login Failed", "Invalid login credentials.");
        return;
    }

    accept();  // بستن دیالوگ
}
