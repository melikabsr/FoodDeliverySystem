

/*

#include "LoginDialog.h"
#include "UserFactory.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

LoginDialog::LoginDialog(ClientNetwork* network, QWidget* parent)
    : QDialog(parent), network(network)
{
    setWindowTitle("🔐 Login");
    resize(300, 180);

    QVBoxLayout* layout = new QVBoxLayout(this);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("✅ Login", this);

    layout->addWidget(new QLabel("👤 Username:", this));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("🔑 Password:", this));
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(network, &ClientNetwork::messageReceived, this, &LoginDialog::onMessageReceived);
}


void LoginDialog::attemptLogin()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();
    UserType type = static_cast<UserType>(roleCombo->currentData().toInt());

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter username and password.");
        return;
    }

    auto tempUser = UserFactory::createUser(type, username, password, username + "@example.com");

    if (tempUser && tempUser->login(username, password)) {
        loggedInUser = std::move(tempUser);
        QMessageBox::information(this, "Login Success", "Welcome, " + username + "!");
        accept();  // بسته‌شدن دیالوگ و بازگشت به MainWindow
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid credentials.");
    }
}

std::unique_ptr<User> LoginDialog::getLoggedInUser() {
    return std::move(loggedInUser);  // انتقال مالکیت به MainWindow
}


QString LoginDialog::getUsername() const
{
    return usernameEdit->text().trimmed();
}




void LoginDialog::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Username and password cannot be empty.");
        return;
    }

    QString role = roleCombo->currentText();
    QString msg = QString("LOGIN|%1|%2|%3").arg(username, password, role);
    network->sendMessage(msg);

    loginButton->setEnabled(false);
}

void LoginDialog::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("LOGIN_RESULT|"))
        return;

    loginButton->setEnabled(true);

    QString result = msg.section("|", 1, 1);
    QString username = usernameEdit->text().trimmed();
    QString roleStr = roleCombo->currentText();

    if (result == "SUCCESS") {
        // ساخت آبجکت User با توجه به نقش
        if (roleStr == "Customer")
            loggedInUser = std::make_unique<Customer>(username);
        else if (roleStr == "RestaurantOwner")
            loggedInUser = std::make_unique<RestaurantOwner>(username);
        else if (roleStr == "Admin")
            loggedInUser = std::make_unique<Admin>(username);

        accept();  // ورود موفق
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username, password or role.");
    }
}


*/




#include "LoginDialog.h"
#include "Customer.h"
#include "RestaurantOwner.h"
#include "Admin.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>

#include "UserFactory.h"

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
    roleCombo->addItems({"Customer", "RestaurantOwner", "Admin"});

    loginButton = new QPushButton("✅ Login", this);

    layout->addWidget(new QLabel("👤 Username:", this));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("🔑 Password:", this));
    layout->addWidget(passwordEdit);
    layout->addWidget(new QLabel("🧩 Role:", this));
    layout->addWidget(roleCombo);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(network, &ClientNetwork::messageReceived, this, &LoginDialog::onMessageReceived);
}

void LoginDialog::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();
    QString role = roleCombo->currentText();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Username and password cannot be empty.");
        return;
    }

    QString msg = QString("LOGIN|%1|%2|%3").arg(username, password, role);
    network->sendMessage(msg);

    loginButton->setEnabled(false);
}

void LoginDialog::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("LOGIN_RESULT|"))
        return;

    loginButton->setEnabled(true);
    QStringList tokens = msg.split("|");
    QString result = tokens[1];
    QString roleStr = (tokens.size() >= 3) ? tokens[2].trimmed().toUpper() : "CUSTOMER";
    QString username = usernameEdit->text().trimmed();

    if (result == "SUCCESS") {
        // ذخیره نقش واقعی برای ارسال به MainWindow
        userRole = roleStr;

        // ساخت کاربر براساس نقش واقعی
        if (roleStr == "CUSTOMER")
            loggedInUser = std::make_unique<Customer>(username);
        else if (roleStr == "RESTAURANT_OWNER")
            loggedInUser = std::make_unique<RestaurantOwner>(username);
        else if (roleStr == "ADMIN")
            loggedInUser = std::make_unique<Admin>(username);
        else {
            QMessageBox::critical(this, "Login Failed", "❌ Unknown role received from server.");
            return;
        }

        accept();  // دیالوگ بسته شود
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username, password or role.");
    }
}


std::unique_ptr<User> LoginDialog::getLoggedInUser()
{
    return std::move(loggedInUser);
}

QString LoginDialog::getUsername() const
{
    return usernameEdit->text().trimmed();
}




void LoginDialog::attemptLogin()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();
    UserType type = static_cast<UserType>(roleCombo->currentData().toInt());

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter username and password.");
        return;
    }

    auto tempUser = UserFactory::createUser(type, username, password, username + "@example.com");

    if (tempUser && tempUser->login(username, password)) {
        loggedInUser = std::move(tempUser);
        QMessageBox::information(this, "Login Success", "Welcome, " + username + "!");
        accept();  // بسته‌شدن دیالوگ و بازگشت به MainWindow
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid credentials.");
    }
}




QString LoginDialog::getRole() const
{
    return userRole;
}

QString LoginDialog::getPassword() const {
    return passwordEdit->text().trimmed();  // فرض بر اینکه passwordEdit وجود داره
}


