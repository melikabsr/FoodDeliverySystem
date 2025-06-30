#ifndef RESTAURANTSERVICE_H
#define RESTAURANTSERVICE_H

#include <QObject>
#include <QVector>
#include "Restaurant.h"

class RestaurantService : public QObject
{
    Q_OBJECT

public:
    static RestaurantService& instance();

    void addRestaurant(const Restaurant& restaurant);
    void removeRestaurant(int id);
    QVector<Restaurant> getAllRestaurants() const;
    int generateNewId() const;

private:
    explicit RestaurantService(QObject* parent = nullptr);
    QVector<Restaurant> restaurants;
};

#endif // RESTAURANTSERVICE_H
