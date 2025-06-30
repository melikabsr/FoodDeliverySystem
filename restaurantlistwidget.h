#ifndef RESTAURANTLISTWIDGET_H
#define RESTAURANTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include "enums.h"

#include "Restaurant.h"

class RestaurantListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantListWidget(QWidget *parent = nullptr);

private:
    QVBoxLayout* mainLayout;
    QList<Restaurant> mockRestaurants;

    void loadRestaurants();
    void displayRestaurants();
};

#endif // RESTAURANTLISTWIDGET_H
