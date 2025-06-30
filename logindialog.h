#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <memory>
#include "User.h"
#include "enums.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    std::unique_ptr<User> getLoggedInUser();  // نسخه non-const برای انتقال مالکیت

private slots:
    void attemptLogin();

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleCombo;
    QPushButton* loginButton;

    std::unique_ptr<User> loggedInUser;
};

#endif // LOGINDIALOG_H

