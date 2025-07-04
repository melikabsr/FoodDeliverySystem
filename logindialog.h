#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "ClientNetwork.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(ClientNetwork* network, QWidget* parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;
    QString getRole() const;

private slots:
    void onLoginClicked();
    void onMessageReceived(const QString& msg);

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleCombo;
    QPushButton* loginButton;
    ClientNetwork* network;
    QString userRole;
};

#endif // LOGINDIALOG_H
