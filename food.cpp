#include "Food.h"

Food::Food()
    : id(0), name(""), price(0.0), description("") {}

Food::Food(int id, const QString& name, double price, const QString& description)
    : id(id), name(name), price(price), description(description) {}

int Food::getId() const {
    return id;
}

QString Food::getName() const {
    return name;
}

double Food::getPrice() const {
    return price;
}

QString Food::getDescription() const {
    return description;
}
