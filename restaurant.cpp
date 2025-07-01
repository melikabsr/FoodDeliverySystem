#include "restaurant.h"
#include "ui_restaurant.h"

Restaurant::Restaurant(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Restaurant)
{
    ui->setupUi(this);
}

Restaurant::~Restaurant()
{
    delete ui;
}
