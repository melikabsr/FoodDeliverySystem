#ifndef FOODREPOSITORY_H
#define FOODREPOSITORY_H

#include <QObject>
#include <QList>
#include "Food.h"

class FoodRepository : public QObject
{
    Q_OBJECT

public:
    explicit FoodRepository(QObject* parent = nullptr);

    QList<Food> getFoodsByRestaurant(int restaurantId);
    bool addFood(int restaurantId, const Food& food);
    bool removeFood(int foodId);
};

#endif // FOODREPOSITORY_H
