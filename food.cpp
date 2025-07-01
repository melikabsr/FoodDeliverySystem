#include "food.h"
#include "ui_food.h"

Food::Food(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Food)
{
    ui->setupUi(this);
}

Food::~Food()
{
    delete ui;
}
