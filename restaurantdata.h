#ifndef RESTAURANTDATA_H
#define RESTAURANTDATA_H

#include <QObject>
#include <QVector>
#include "Restaurant.h"

class RestaurantData : public QObject
{
    Q_OBJECT

public:
    static RestaurantData& instance();

    void addRestaurant(const Restaurant& restaurant);
    void removeRestaurant(int id);
    QVector<Restaurant> getAllRestaurants() const;
    QString serializeRestaurants() const;
    int generateNewId() const;

private:
    explicit RestaurantData(QObject* parent = nullptr);
    QVector<Restaurant> restaurants;
};

#endif // RESTAURANTDATA_H
