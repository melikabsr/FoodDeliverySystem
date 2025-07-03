#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "ClientNetwork.h"
#include <QTableWidget>
class AdminPanel : public QWidget
{
    Q_OBJECT

public:
   //explicit AdminPanel(QWidget *parent = nullptr);
    explicit AdminPanel(ClientNetwork* net, QWidget *parent = nullptr);

private slots:
    void onViewUsersClicked();
    void onViewOrdersClicked();
    void onExitClicked();

private:
    QLabel* titleLabel;
    QPushButton* viewUsersBtn;
    QPushButton* viewOrdersBtn;
    QPushButton* exitBtn;
    QVBoxLayout* layout;
     ClientNetwork* network;

    QTableWidget* ordersTable;

public slots:
     void refreshOrders();
};

#endif // ADMINPANEL_H
