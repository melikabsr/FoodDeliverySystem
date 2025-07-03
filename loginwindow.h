#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "clientnetwork.h"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;
    QString getRole() const;


private slots:
    void onLoginClicked();
    void onMessageReceived(const QString& msg);
    void onNetworkError(const QString& err);

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleCombo;
    QPushButton* loginButton;
    QLabel* statusLabel;

    ClientNetwork* network;
};

#endif // LOGINWINDOW_H
