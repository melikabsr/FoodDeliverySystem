#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QList>
#include "Food.h"

class Restaurant
{
public:
    Restaurant();
    Restaurant(int id, const QString& name, const QString& address);

    int getId() const;
    QString getName() const;
    QString getAddress() const;

    void setName(const QString& name);
    void setAddress(const QString& address);

    QList<Food> getMenu() const;
    void addFood(const Food& food);
    void removeFood(int foodId);
    QString serializeMenu() const;

private:
    int id;
    QString name;
    QString address;
    QList<Food> menu;
};

#endif // RESTAURANT_H
