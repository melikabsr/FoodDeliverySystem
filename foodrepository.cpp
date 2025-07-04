#include "FoodRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

FoodRepository::FoodRepository(QObject* parent)
    : QObject(parent)
{
}

QList<Food> FoodRepository::getFoodsByRestaurant(int restaurantId)
{
    QList<Food> list;
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT id, name, description, price FROM foods WHERE restaurant_id = ?");
    query.addBindValue(restaurantId);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString desc = query.value(2).toString();
            double price = query.value(3).toDouble();

            list.append(Food(id, name, desc, price, FoodCategory::FAST_FOOD, ""));
        }
    } else {
        qWarning() << "Failed to fetch foods:" << query.lastError().text();
    }

    return list;
}

bool FoodRepository::addFood(int restaurantId, const Food& food)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("INSERT INTO foods (restaurant_id, name, description, price) VALUES (?, ?, ?, ?)");
    query.addBindValue(restaurantId);
    query.addBindValue(food.getName());
    query.addBindValue(food.getDescription());
    query.addBindValue(food.getPrice());

    if (!query.exec()) {
        qWarning() << "Failed to add food:" << query.lastError().text();
        return false;
    }
    return true;
}

bool FoodRepository::removeFood(int foodId)
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("DELETE FROM foods WHERE id = ?");
    query.addBindValue(foodId);

    if (!query.exec()) {
        qWarning() << "Failed to remove food:" << query.lastError().text();
        return false;
    }
    return true;
}
