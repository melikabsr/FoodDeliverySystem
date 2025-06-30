#include "AddFoodDialog.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include "enums.h"

AddFoodDialog::AddFoodDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("➕ Add New Food");
    resize(300, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Food name");

    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("Description");

    priceEdit = new QLineEdit(this);
    priceEdit->setPlaceholderText("Price (e.g. 10.5)");

    imagePathEdit = new QLineEdit(this);
    imagePathEdit->setPlaceholderText("Image path (optional)");

    categoryCombo = new QComboBox(this);
    categoryCombo->addItem("Fast Food", QVariant::fromValue(int(FoodCategory::FAST_FOOD)));
    categoryCombo->addItem("Iranian", QVariant::fromValue(int(FoodCategory::IRANIAN)));
    categoryCombo->addItem("Pizza", QVariant::fromValue(int(FoodCategory::PIZZA)));
    categoryCombo->addItem("Drinks", QVariant::fromValue(int(FoodCategory::DRINKS)));
    categoryCombo->addItem("Dessert", QVariant::fromValue(int(FoodCategory::DESSERT)));

    submitBtn = new QPushButton("Submit", this);

    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Description:"));
    layout->addWidget(descriptionEdit);
    layout->addWidget(new QLabel("Price:"));
    layout->addWidget(priceEdit);
    layout->addWidget(new QLabel("Category:"));
    layout->addWidget(categoryCombo);
    layout->addWidget(new QLabel("Image Path:"));
    layout->addWidget(imagePathEdit);
    layout->addWidget(submitBtn);

    connect(submitBtn, &QPushButton::clicked, this, &AddFoodDialog::submit);
}

void AddFoodDialog::submit()
{
    QString name = nameEdit->text().trimmed();
    QString description = descriptionEdit->text().trimmed();
    QString priceStr = priceEdit->text().trimmed();
    double price = priceStr.toDouble();
    int categoryVal = categoryCombo->currentData().toInt();
    QString imagePath = imagePathEdit->text().trimmed();

    if (name.isEmpty() || description.isEmpty() || price <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please fill all fields correctly.");
        return;
    }

    static int nextId = 1000;
    newFood = Food(nextId++, name, description, price, static_cast<FoodCategory>(categoryVal), imagePath);
    accept();
}

Food AddFoodDialog::getNewFood() const
{
    return newFood;
}
