#include "Restaurant.h"

Restaurant::Restaurant()
    : id(0), name(""), address("") {}

Restaurant::Restaurant(int id, const QString& name, const QString& address)
    : id(id), name(name), address(address) {}

int Restaurant::getId() const { return id; }

QString Restaurant::getName() const { return name; }

QString Restaurant::getAddress() const { return address; }

QList<Food> Restaurant::getMenu() const { return menu; }

void Restaurant::addFood(const Food& food) {
    menu.append(food);
}

void Restaurant::setMenu(const QList<Food>& newMenu) {
    menu = newMenu;
}
