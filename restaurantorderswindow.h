#ifndef RESTAURANTORDERSWINDOW_H
#define RESTAURANTORDERSWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ClientNetwork.h"

class RestaurantOrdersWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantOrdersWindow(int restaurantId, ClientNetwork* network, QWidget* parent = nullptr);

private slots:
    void handleOrderResponse(const QString& message);
    void updateOrderStatus(int orderId, const QString& newStatus);

private:
    int restaurantId;
    ClientNetwork* clientNetwork;
    QVBoxLayout* mainLayout;
    QScrollArea* scrollArea;

    void requestOrders();
};

#endif // RESTAURANTORDERSWINDOW_H

