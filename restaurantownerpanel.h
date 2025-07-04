#ifndef RESTAURANTOWNERPANEL_H
#define RESTAURANTOWNERPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QGroupBox>
#include "Food.h"
#include "ClientNetwork.h"

class RestaurantOwnerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantOwnerPanel(ClientNetwork* network, int restaurantId, QWidget* parent = nullptr);

public slots:
    void refreshOrders();
    void updateMenuDisplay(const QList<Food>& menu);

private slots:
    void showMenu();
    void addFood();
    void viewOrders();
    void logout();
    void removeFoodFromMenu(int foodId, QGroupBox* box);

private:
    ClientNetwork* clientNetwork;
    int restaurantId;
    QVector<Food> myMenu;

    QLabel* welcomeLabel;
    QTextEdit* ordersTextEdit;
    QPushButton* viewMenuButton;
    QPushButton* addFoodButton;
    QPushButton* viewOrdersButton;
    QPushButton* logoutButton;

    QWidget* menuWindow = nullptr;
    QVBoxLayout* menuLayout = nullptr;
};

#endif // RESTAURANTOWNERPANEL_H
