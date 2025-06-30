#include "LoginDialog.h"
#include "UserFactory.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Login");

    QLabel* userLabel = new QLabel("Username:");
    QLabel* passLabel = new QLabel("Password:");
    QLabel* roleLabel = new QLabel("User Type:");

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    roleCombo = new QComboBox(this);
    roleCombo->addItem("Customer", QVariant::fromValue(int(UserType::CUSTOMER)));
    roleCombo->addItem("Restaurant Owner", QVariant::fromValue(int(UserType::RESTAURANT_OWNER)));
    roleCombo->addItem("Admin", QVariant::fromValue(int(UserType::ADMIN)));

    loginButton = new QPushButton("Login");

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(userLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(roleLabel);
    layout->addWidget(roleCombo);
    layout->addWidget(loginButton);

    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::attemptLogin);
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

