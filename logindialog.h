#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <memory>
#include "User.h"
#include "enums.h"
#include "ClientNetwork.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(ClientNetwork* network, QWidget* parent = nullptr);
   // explicit LoginDialog(QWidget *parent = nullptr);
    std::unique_ptr<User> getLoggedInUser();  // نسخه non-const برای انتقال مالکیت


  QString getUsername() const;
  QString getPassword() const;
  QString getRole() const;

private slots:
    void attemptLogin();
    void onLoginClicked();
    void onMessageReceived(const QString& msg);


private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleCombo;
    QPushButton* loginButton;
    ClientNetwork* network;
    QString userRole;

    std::unique_ptr<User> loggedInUser;
};

#endif // LOGINDIALOG_H

