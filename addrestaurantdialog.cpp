#include "AddRestaurantDialog.h"
#include "RestaurantService.h"
#include "Restaurant.h"
#include <QMessageBox>

AddRestaurantDialog::AddRestaurantDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("➕ Add New Restaurant");
    resize(300, 200);

    QVBoxLayout* layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Restaurant Name");

    addressEdit = new QLineEdit(this);
    addressEdit->setPlaceholderText("Address");

    submitBtn = new QPushButton("✅ Submit");
    cancelBtn = new QPushButton("❌ Cancel");

    layout->addWidget(nameEdit);
    layout->addWidget(addressEdit);
    layout->addWidget(submitBtn);
    layout->addWidget(cancelBtn);

    connect(submitBtn, &QPushButton::clicked, this, &AddRestaurantDialog::onSubmit);
    connect(cancelBtn, &QPushButton::clicked, this, &AddRestaurantDialog::reject);
}

void AddRestaurantDialog::onSubmit()
{
    QString name = nameEdit->text().trimmed();
    QString address = addressEdit->text().trimmed();

    if (name.isEmpty() || address.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "لطفاً تمام فیلدها را پر کنید.");
        return;
    }

    Restaurant newRestaurant(RestaurantService::instance().generateNewId(), name, address);
    RestaurantService::instance().addRestaurant(newRestaurant);
    accept();
}
