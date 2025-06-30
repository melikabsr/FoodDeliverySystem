#include "addrestaurantdialog.h"
#include "ui_addrestaurantdialog.h"

AddRestaurantDialog::AddRestaurantDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddRestaurantDialog)
{
    ui->setupUi(this);
}

AddRestaurantDialog::~AddRestaurantDialog()
{
    delete ui;
}
