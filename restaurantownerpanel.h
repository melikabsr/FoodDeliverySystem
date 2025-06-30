#ifndef RESTAURANTOWNERPANEL_H
#define RESTAURANTOWNERPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Food.h"
#include <QList>

class RestaurantOwnerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantOwnerPanel(QWidget *parent = nullptr);

private slots:
    void showMenu();
    void addFood();
    void viewOrders();
    void logout();

private:
    QLabel* welcomeLabel;
    QPushButton* viewMenuButton;
    QPushButton* addFoodButton;
    QPushButton* viewOrdersButton;
    QPushButton* logoutButton;
    QList<Food> myMenu;  // لیست غذاهای رستوران جاری

};

#endif // RESTAURANTOWNERPANEL_H
