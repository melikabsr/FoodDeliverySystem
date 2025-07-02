#include "AddFoodDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QLabel>

AddFoodDialog::AddFoodDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("➕ Add New Food");
    resize(350, 300);

    nameEdit = new QLineEdit(this);
    descriptionEdit = new QLineEdit(this);
    priceEdit = new QLineEdit(this);
    imagePathEdit = new QLineEdit(this);
    categoryCombo = new QComboBox(this);

    nameEdit->setPlaceholderText("Name");
    descriptionEdit->setPlaceholderText("Description");
    priceEdit->setPlaceholderText("Price");
    imagePathEdit->setPlaceholderText("Image Path (optional)");

    categoryCombo->addItem("Fast Food", QVariant::fromValue(int(FoodCategory::FAST_FOOD)));
    categoryCombo->addItem("Iranian", QVariant::fromValue(int(FoodCategory::IRANIAN)));
    categoryCombo->addItem("Pizza", QVariant::fromValue(int(FoodCategory::PIZZA)));
    categoryCombo->addItem("Drinks", QVariant::fromValue(int(FoodCategory::DRINKS)));
    categoryCombo->addItem("Dessert", QVariant::fromValue(int(FoodCategory::DESSERT)));

    auto* layout = new QVBoxLayout(this);
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

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &AddFoodDialog::submit);
    connect(buttons, &QDialogButtonBox::rejected, this, &AddFoodDialog::reject);
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
