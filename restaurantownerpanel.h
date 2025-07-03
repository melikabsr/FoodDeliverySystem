#ifndef RESTAURANTOWNERPANEL_H
#define RESTAURANTOWNERPANEL_H

#include <QWidget>
#include <QVector>
#include <QList>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include "Food.h"
#include "Order.h"

class ClientNetwork;
class QLabel;
class QPushButton;

class RestaurantOwnerPanel : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantOwnerPanel(ClientNetwork* network, int restaurantId, QWidget* parent = nullptr);

private slots:
    void showMenu();
    void addFood();
    void viewOrders();
    void logout();
    void updateMenuDisplay(const QList<Food>& menu);
    void removeFoodFromMenu(int foodId, QGroupBox* boxToRemove);
public slots:
    void refreshOrders();
private:
    ClientNetwork* clientNetwork;
    int restaurantId;

    QVector<Food> myMenu;



    QTextEdit* ordersTextEdit;
    QLabel* welcomeLabel;
    QPushButton* viewMenuButton;
    QPushButton* addFoodButton;
    QPushButton* viewOrdersButton;
    QPushButton* logoutButton;

    QWidget* menuWindow = nullptr;
    QVBoxLayout* menuLayout = nullptr;
};

#endif // RESTAURANTOWNERPANEL_H
