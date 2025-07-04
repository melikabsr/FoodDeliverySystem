#include "restaurant.h"

Restaurant::Restaurant() : id(0), name(""), address(""), ownerUsername("") {}
Restaurant::Restaurant(int id, const QString& name, const QString& address, const QString& owner)
    : id(id), name(name), address(address), ownerUsername(owner) {}

int Restaurant::getId() const { return id; }
QString Restaurant::getName() const { return name; }
QString Restaurant::getAddress() const { return address; }
QString Restaurant::getOwnerUsername() const { return ownerUsername; }

void Restaurant::setName(const QString& name) { this->name = name; }
void Restaurant::setAddress(const QString& address) { this->address = address; }
void Restaurant::setOwnerUsername(const QString& owner) { this->ownerUsername = owner; }

QList<Food> Restaurant::getMenu() const { return menu; }
void Restaurant::addFood(const Food& food) { menu.append(food); }
void Restaurant::removeFood(int foodId) {
    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getId() == foodId) {
            menu.removeAt(i);
            break;
        }
    }
}
bool Restaurant::removeFoodById(int foodId) {
    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getId() == foodId) {
            menu.removeAt(i);
            return true;
        }
    }
    return false;
}
QString Restaurant::serializeMenu() const {
    QStringList items;
    for (const Food& food : menu) {
        items.append(QString("%1~%2~%3~%4")
                         .arg(food.getId())
                         .arg(food.getName())
                         .arg(food.getPrice())
                         .arg(food.getDescription()));
    }
    return items.join("|");
}



Restaurant::Restaurant(int id, const QString& name, const QString& address)
    : id(id), name(name), address(address), ownerUsername("") {}
