#include "Restaurant.h"

Restaurant::Restaurant(int id, const QString& name, const QString& address, bool active)
    : id(id), name(name), address(address), isActive(active)
{
}

int Restaurant::getId() const {
    return id;
}

QString Restaurant::getName() const {
    return name;
}

QString Restaurant::getAddress() const {
    return address;
}

bool Restaurant::getStatus() const {
    return isActive;
}

void Restaurant::addFood(const Food& food) {
    menu.append(food);
}

void Restaurant::removeFood(int foodId) {
    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getId() == foodId) {
            menu.removeAt(i);
            return;
        }
    }
}

QList<Food> Restaurant::getMenu() const {
    return menu;
}
