#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QList>
#include "Food.h"

class Restaurant {
private:
    int id;
    QString name;
    QString address;
    QString ownerUsername;
    QList<Food> menu;

public:
    Restaurant();
    Restaurant(int id, const QString& name, const QString& address, const QString& ownerUsername);
    Restaurant(int id, const QString& name, const QString& address);

    int getId() const;
    QString getName() const;
    QString getAddress() const;
    QString getOwnerUsername() const;

    void setName(const QString& name);
    void setAddress(const QString& address);
    void setOwnerUsername(const QString& owner);

    QList<Food> getMenu() const;
    void addFood(const Food& food);
    void removeFood(int foodId);
    bool removeFoodById(int foodId);
    QString serializeMenu() const;
};

#endif // RESTAURANT_H
