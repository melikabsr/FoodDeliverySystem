#include "Food.h"

Food::Food()
    : id(0), name(""), description(""), price(0.0),
    category(FoodCategory::MAIN_COURSE), imagePath("") {}

Food::Food(int id, const QString& name, const QString& description,
           double price, FoodCategory category, const QString& imagePath)
    : id(id), name(name), description(description),
    price(price), category(category), imagePath(imagePath) {}

Food::Food(const Food& other)
    : id(other.id),
    name(other.name),
    description(other.description),
    price(other.price),
    category(other.category),
    imagePath(other.imagePath) {}

int Food::getId() const { return id; }
QString Food::getName() const { return name; }
QString Food::getDescription() const { return description; }
double Food::getPrice() const { return price; }
FoodCategory Food::getCategory() const { return category; }
QString Food::getImagePath() const { return imagePath; }




