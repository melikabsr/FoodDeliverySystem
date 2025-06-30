#include "RestaurantService.h"

RestaurantService::RestaurantService(QObject* parent)
    : QObject(parent)
{
    // در صورت نیاز می‌توان اینجا داده اولیه اضافه کرد
}

RestaurantService& RestaurantService::instance()
{
    static RestaurantService service;
    return service;
}

void RestaurantService::addRestaurant(const Restaurant& restaurant)
{
    restaurants.append(restaurant);
}

void RestaurantService::removeRestaurant(int id)
{
    for (int i = 0; i < restaurants.size(); ++i) {
        if (restaurants[i].getId() == id) {
            restaurants.removeAt(i);
            break;
        }
    }
}

QVector<Restaurant> RestaurantService::getAllRestaurants() const
{
    return restaurants;
}

int RestaurantService::generateNewId() const
{
    int maxId = 0;
    for (const auto& r : restaurants) {
        if (r.getId() > maxId)
            maxId = r.getId();
    }
    return maxId + 1;
}
