#ifndef RESTAURANTADMINWIDGET_H
#define RESTAURANTADMINWIDGET_H

#include <QDialog>

namespace Ui {
class RestaurantAdminWidget;
}

class RestaurantAdminWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RestaurantAdminWidget(QWidget *parent = nullptr);
    ~RestaurantAdminWidget();

private:
    Ui::RestaurantAdminWidget *ui;
};

#endif // RESTAURANTADMINWIDGET_H
