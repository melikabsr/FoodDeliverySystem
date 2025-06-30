#include "Food.h"

Food::Food(int id,
           const QString& name,
           const QString& description,
           double price,
           FoodCategory category,
           const QString& imagePath)
    : id(id), name(name), description(description),
    price(price), category(category), imagePath(imagePath)
{
}

int Food::getId() const {
    return id;
}

QString Food::getName() const {
    return name;
}

QString Food::getDescription() const {
    return description;
}

double Food::getPrice() const {
    return price;
}

FoodCategory Food::getCategory() const {
    return category;
}

QString Food::getImagePath() const {
    return imagePath;
}
