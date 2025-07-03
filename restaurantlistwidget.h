#ifndef RESTAURANTLISTWIDGET_H
#define RESTAURANTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include "enums.h"
#include <QListWidget>
#include <QMap>
#include "ClientNetwork.h"

#include "Restaurant.h"

class RestaurantListWidget : public QWidget
{
    Q_OBJECT

public:
    //explicit RestaurantListWidget(QWidget *parent = nullptr);
     // explicit RestaurantListWidget(ClientNetwork* network, QWidget* parent = nullptr);
   // explicit RestaurantListWidget(ClientNetwork* network, const QString& username, QWidget* parent = nullptr);
    explicit RestaurantListWidget(ClientNetwork* network, QWidget* parent = nullptr);
    explicit RestaurantListWidget(ClientNetwork* network, const QString& username, QWidget* parent = nullptr);

private:
    QVBoxLayout* mainLayout;
    QList<Restaurant> mockRestaurants;

    void loadRestaurants();
    void displayRestaurants();


    QString username;

    ClientNetwork* network;
    QListWidget* listWidget;
    QMap<QListWidgetItem*, int> itemToId;

private slots:
    void onMessageReceived(const QString& msg);
    void onRestaurantSelected(QListWidgetItem* item);

};

#endif // RESTAURANTLISTWIDGET_H



