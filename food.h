// #ifndef FOOD_H
// #define FOOD_H

// #include <QString>

// class Food
// {
// public:
//     Food();
//     Food(int id, const QString& name, double price, const QString& description);

//     int getId() const;
//     QString getName() const;
//     double getPrice() const;
//     QString getDescription() const;
// //    int getRestaurantId() const ;

// private:
//     int id;
//     QString name;
//     double price;
//     QString description;
//   //  int restaurantId ;
// };

// #endif // FOOD_H
#ifndef FOOD_H
#define FOOD_H

#include <QString>

enum class FoodCategory {
    FAST_FOOD,
    TRADITIONAL,
    VEGETARIAN,
    DESSERT,
    DRINK
};

class Food
{
public:
    Food();
    Food(int id, const QString& name, const QString& description, double price,
         FoodCategory category, const QString& imagePath);

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    double getPrice() const;
    FoodCategory getCategory() const;
    QString getImagePath() const;

    void setName(const QString& name);
    void setDescription(const QString& description);
    void setPrice(double price);
    void setCategory(FoodCategory category);
    void setImagePath(const QString& path);

    QString serialize() const;
    static Food deserialize(const QString& str);

private:
    int id;
    QString name;
    QString description;
    double price;
    FoodCategory category;
    QString imagePath;
};

QString foodCategoryToString(FoodCategory category);
FoodCategory foodCategoryFromString(const QString& str);

#endif // FOOD_H
