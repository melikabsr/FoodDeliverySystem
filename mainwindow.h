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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void onExitClicked();

private:
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QMenuBar* menuBar;
    QMenu* fileMenu;
    QAction* loginAction;
    QAction* exitAction;
};

#endif // MAINWINDOW_H



