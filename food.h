#ifndef FOOD_H
#define FOOD_H

#include <QString>
#include "enums.h"

class Food
{
private:
    int id;
    QString name;
    QString description;
    double price;
    FoodCategory category;
    QString imagePath;

public:
    Food(int id,
         const QString& name,
         const QString& description,
         double price,
         FoodCategory category,
         const QString& imagePath = "");

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    double getPrice() const;
    FoodCategory getCategory() const;
    QString getImagePath() const;
};

#endif // FOOD_H
