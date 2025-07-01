#include "Restaurant.h"

Restaurant::Restaurant() : id(0), name(""), address("") {}

Restaurant::Restaurant(int id, const QString& name, const QString& address)
    : id(id), name(name), address(address) {}

int Restaurant::getId() const { return id; }
QString Restaurant::getName() const { return name; }
QString Restaurant::getAddress() const { return address; }

void Restaurant::setName(const QString& name) { this->name = name; }
void Restaurant::setAddress(const QString& address) { this->address = address; }

QList<Food> Restaurant::getMenu() const { return menu; }

void Restaurant::addFood(const Food& food) {
    menu.append(food);
}

void Restaurant::removeFood(int foodId) {
    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getId() == foodId) {
            menu.removeAt(i);
            break;
        }
    }
}

QString Restaurant::serializeMenu() const {
    QStringList items;
    for (const Food& food : menu) {
        items.append(QString("%1,%2,%3,%4")
                         .arg(food.getId())
                         .arg(food.getName())
                         .arg(food.getPrice())
                         .arg(food.getDescription()));
    }
    return items.join(";");
}
