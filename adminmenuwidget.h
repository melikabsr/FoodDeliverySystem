#ifndef ADMINMENUWIDGET_H
#define ADMINMENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include "Restaurant.h"

class QListWidget;
class QPushButton;

class AdminMenuWidget : public QWidget
{
    Q_OBJECT

public:
   // explicit AdminMenuWidget(const Restaurant& restaurant, QWidget *parent = nullptr);
    explicit AdminMenuWidget(Restaurant& restaurant, QWidget *parent = nullptr);

private slots:
    void onAddFoodClicked();
    void onRemoveFoodClicked();
    void refreshMenu();

private:
    Restaurant restaurant;
    QListWidget* foodList;
    QPushButton* addFoodBtn;
    QPushButton* removeFoodBtn;
};

#endif // ADMINMENUWIDGET_H
