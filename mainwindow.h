#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include "LoginDialog.h"
#include "User.h"
#include "CustomerPanel.h"
#include "Restaurant.h"
#include "ClientNetwork.h"
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showWelcomeScreen();

private slots:
    void onLoginClicked();
    void onExitClicked();
    void onMessageReceived(const QString& msg);  // ✅ حالا تعریف شده

private:

    QVBoxLayout* mainLayout;
    QMenuBar* menuBar;
    QMenu* fileMenu;
    QAction* loginAction;
    QAction* exitAction;
    ClientNetwork* network;
    QLabel* statusLabel;
    QString username;
};

#endif // MAINWINDOW_H
