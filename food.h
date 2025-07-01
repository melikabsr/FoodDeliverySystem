#ifndef FOOD_H
#define FOOD_H

#include <QString>

class Food
{
public:
    Food();
    Food(int id, const QString& name, double price, const QString& description);

    int getId() const;
    QString getName() const;
    double getPrice() const;
    QString getDescription() const;

private:
    int id;
    QString name;
    double price;
    QString description;
};

#endif // FOOD_H
