#ifndef RESTAURANTREPOSITORY_H
#define RESTAURANTREPOSITORY_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include "Restaurant.h"

class RestaurantRepository : public QObject
{
    Q_OBJECT

public:
    static RestaurantRepository& instance();

    bool addRestaurant(const Restaurant& restaurant);
    QVector<Restaurant> getAllRestaurants();
    Restaurant getRestaurantById(int id);
    bool removeRestaurant(int id);

public:
    explicit RestaurantRepository(QObject* parent = nullptr);
};

#endif // RESTAURANTREPOSITORY_H
