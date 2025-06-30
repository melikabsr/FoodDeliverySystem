#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QList>
#include "Food.h"

class Restaurant
{
private:
    int id;
    QString name;
    QString address;
    QList<Food> menu;

public:
    Restaurant();
    Restaurant(int id, const QString& name, const QString& address);

    int getId() const;
    QString getName() const;
    QString getAddress() const;
    QList<Food> getMenu() const;
    void removeFood(int foodId);
    void setName(const QString& name);
    void setAddress(const QString& address);
    void addFood(const Food& food);
    void setMenu(const QList<Food>& newMenu);
};

#endif // RESTAURANT_H




