#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <memory>

#include "User.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    std::unique_ptr<User> getLoggedInUser() const;

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
