#include "Food.h"
#include <QStringList>

Food::Food() : id(0), price(0.0), category(FoodCategory::FAST_FOOD) {}

Food::Food(int id, const QString& name, const QString& description, double price,
           FoodCategory category, const QString& imagePath)
    : id(id), name(name), description(description), price(price), category(category), imagePath(imagePath) {}

int Food::getId() const { return id; }
QString Food::getName() const { return name; }
QString Food::getDescription() const { return description; }
double Food::getPrice() const { return price; }
FoodCategory Food::getCategory() const { return category; }
QString Food::getImagePath() const { return imagePath; }

void Food::setName(const QString& n) { name = n; }
void Food::setDescription(const QString& d) { description = d; }
void Food::setPrice(double p) { price = p; }
void Food::setCategory(FoodCategory c) { category = c; }
void Food::setImagePath(const QString& path) { imagePath = path; }

QString Food::serialize() const {
    return QString("%1~%2~%3~%4~%5~%6")
    .arg(id)
        .arg(name)
        .arg(description)
        .arg(price)
        .arg(foodCategoryToString(category))
        .arg(imagePath);
}

Food Food::deserialize(const QString& str) {
    QStringList parts = str.split("~");
    if (parts.size() < 6) return Food();

    int id = parts[0].toInt();
    QString name = parts[1];
    QString desc = parts[2];
    double price = parts[3].toDouble();
    FoodCategory category = foodCategoryFromString(parts[4]);
    QString imagePath = parts[5];

    return Food(id, name, desc, price, category, imagePath);
}

QString foodCategoryToString(FoodCategory category) {
    switch (category) {
    case FoodCategory::FAST_FOOD: return "FAST_FOOD";
    case FoodCategory::TRADITIONAL: return "TRADITIONAL";
    case FoodCategory::VEGETARIAN: return "VEGETARIAN";
    case FoodCategory::DESSERT: return "DESSERT";
    case FoodCategory::DRINK: return "DRINK";
    default: return "UNKNOWN";
    }
}

FoodCategory foodCategoryFromString(const QString& str) {
    if (str == "FAST_FOOD") return FoodCategory::FAST_FOOD;
    if (str == "TRADITIONAL") return FoodCategory::TRADITIONAL;
    if (str == "VEGETARIAN") return FoodCategory::VEGETARIAN;
    if (str == "DESSERT") return FoodCategory::DESSERT;
    if (str == "DRINK") return FoodCategory::DRINK;
    return FoodCategory::FAST_FOOD;
}
