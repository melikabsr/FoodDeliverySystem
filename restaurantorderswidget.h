#ifndef RESTAURANTORDERSWIDGET_H
#define RESTAURANTORDERSWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "ClientNetwork.h"
#include <QVBoxLayout>
#include <QMap>
class ClientNetwork;
class RestaurantOrdersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantOrdersWidget(ClientNetwork* network, int restaurantId, QWidget* parent = nullptr);

private slots:
    void onMessageReceived(const QString& msg);
    void onStatusChangeClicked();
    void refreshOrders();
  //    void onEditClicked();

private:
    ClientNetwork* network;
    int rId;
    QListWidget* orderList;
    QPushButton* refreshBtn;
    QPushButton* changeStatusBtn;



    QString rName;
    QListWidget* listWidget;
    QMap<QListWidgetItem*, int> itemToOrderId;
};

#endif // RESTAURANTORDERSWIDGET_H

