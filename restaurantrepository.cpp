#include "RestaurantRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

RestaurantRepository::RestaurantRepository(QObject* parent)
    : QObject(parent) {}

RestaurantRepository& RestaurantRepository::instance()
{
    static RestaurantRepository repo;
    return repo;
}

bool RestaurantRepository::addRestaurant(const Restaurant& r)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("INSERT INTO restaurants (name, address, owner_username) VALUES (?, ?, ?)");
    query.addBindValue(r.getName());
    query.addBindValue(r.getAddress());
    query.addBindValue(r.getOwnerUsername());
    return query.exec();
}

QVector<Restaurant> RestaurantRepository::getAllRestaurants()
{
    QVector<Restaurant> list;
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT id, name, address, owner_username FROM restaurants");
    if (query.exec()) {
        while (query.next()) {
            list.append(Restaurant(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toString()));
        }
    }
    return list;
}

Restaurant RestaurantRepository::getRestaurantById(int id)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT name, address, owner_username FROM restaurants WHERE id = ?");
    query.addBindValue(id);
    if (query.exec() && query.next()) {
        return Restaurant(id,
                          query.value(0).toString(),
                          query.value(1).toString(),
                          query.value(2).toString());
    }
    return Restaurant();
}

bool RestaurantRepository::removeRestaurant(int id)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("DELETE FROM restaurants WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}
