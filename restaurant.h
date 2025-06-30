#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QList>
#include "Food.h"
#include "enums.h"

class Restaurant
{
private:
    int id;
    QString name;
    QString address;
    QList<Food> menu;
    bool isActive;

public:
    Restaurant(int id, const QString& name, const QString& address, bool active = true);

    int getId() const;
    QString getName() const;
    QString getAddress() const;
    bool getStatus() const;

    void addFood(const Food& food);
    void removeFood(int foodId);
    QList<Food> getMenu() const;
};

#endif // RESTAURANT_H
