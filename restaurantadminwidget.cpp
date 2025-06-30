#include "restaurantadminwidget.h"
#include "ui_restaurantadminwidget.h"

RestaurantAdminWidget::RestaurantAdminWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RestaurantAdminWidget)
{
    ui->setupUi(this);
}

RestaurantAdminWidget::~RestaurantAdminWidget()
{
    delete ui;
}
