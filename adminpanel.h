#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "ClientNetwork.h"

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(ClientNetwork* net, QWidget *parent = nullptr);

private slots:
    void onViewUsersClicked();
    void onViewOrdersClicked();
    void onExitClicked();
    void onMessageReceived(const QString& msg);

private:
    QLabel* titleLabel;
    QPushButton* viewUsersBtn;
    QPushButton* viewOrdersBtn;
    QPushButton* exitBtn;
    QVBoxLayout* layout;
    ClientNetwork* network;
    QTableWidget* ordersTable;
};

#endif // ADMINPANEL_H

