#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QLabel>
#include "LoginDialog.h"
#include "ClientNetwork.h"
#include "CustomerPanel.h"
#include "RestaurantOwnerPanel.h"
#include "AdminPanel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 void showWelcomeScreen();
public slots:
    void onMessageReceived(const QString& msg);

private slots:
    void onLoginClicked();
    void onExitClicked();

private:
    QMenuBar* menuBar;
    QMenu* fileMenu;
    QAction* loginAction;
    QAction* exitAction;
    ClientNetwork* network;
    QLabel* statusLabel;
    QString username;
    QString userRole;


};

#endif // MAINWINDOW_H

