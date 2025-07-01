#include "RestaurantData.h"

RestaurantData::RestaurantData(QObject* parent)
    : QObject(parent)
{
    // چند رستوران نمونه
    restaurants.append(Restaurant(1, "Pizza Land", "Valiasr St."));
    restaurants.append(Restaurant(2, "Kebab Time", "Enghelab Sq."));
    restaurants.append(Restaurant(3, "Veggie House", "Jordan Blvd."));
}

RestaurantData& RestaurantData::instance()
{
    static RestaurantData data;
    return data;
}

void RestaurantData::addRestaurant(const Restaurant& restaurant)
{
    restaurants.append(restaurant);
}

void RestaurantData::removeRestaurant(int id)
{
    for (int i = 0; i < restaurants.size(); ++i) {
        if (restaurants[i].getId() == id) {
            restaurants.removeAt(i);
            break;
        }
    }
}

QVector<Restaurant> RestaurantData::getAllRestaurants() const
{
    return restaurants;
}

int RestaurantData::generateNewId() const
{
    int maxId = 0;
    for (const auto& r : restaurants) {
        if (r.getId() > maxId)
            maxId = r.getId();
    }
    return maxId + 1;
}

QString RestaurantData::serializeRestaurants() const
{
    QStringList list;
    for (const auto& r : restaurants) {
        list.append(QString("%1,%2,%3").arg(r.getId()).arg(r.getName()).arg(r.getAddress()));
    }
    return list.join(";");
}



const Restaurant* RestaurantData::getRestaurantById(int id) const {
    for (const Restaurant& r : restaurants) {
        if (r.getId() == id)
            return &r;
    }
    return nullptr;
}
