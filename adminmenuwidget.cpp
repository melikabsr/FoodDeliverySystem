#include "AdminMenuWidget.h"
#include "Food.h"
#include "AddFoodDialog.h"
#include <QHBoxLayout>
#include <QMessageBox>

AdminMenuWidget::AdminMenuWidget(const Restaurant& restaurant, QWidget *parent)
    : QWidget(parent), restaurant(restaurant)
{
    setWindowTitle("🍽️ Menu Management - " + restaurant.getName());
    resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    foodList = new QListWidget(this);
    layout->addWidget(foodList);

    addFoodBtn = new QPushButton("➕ Add Food");
    removeFoodBtn = new QPushButton("❌ Remove Selected Food");
    layout->addWidget(addFoodBtn);
    layout->addWidget(removeFoodBtn);

    connect(addFoodBtn, &QPushButton::clicked, this, &AdminMenuWidget::onAddFoodClicked);
    connect(removeFoodBtn, &QPushButton::clicked, this, &AdminMenuWidget::onRemoveFoodClicked);

    refreshMenu();
}

void AdminMenuWidget::refreshMenu()
{
    foodList->clear();
    const auto& menu = restaurant.getMenu();
    for (const Food& food : menu) {
        QString info = QString("%1 - %2 $").arg(food.getName()).arg(food.getPrice());
        QListWidgetItem* item = new QListWidgetItem(info);
        item->setData(Qt::UserRole, food.getId());
        foodList->addItem(item);
    }
}

void AdminMenuWidget::onAddFoodClicked()
{
    AddFoodDialog dialog(restaurant, this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshMenu();
    }
}

void AdminMenuWidget::onRemoveFoodClicked()
{
    auto item = foodList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "No Selection", "Please select a food item to remove.");
        return;
    }

    int foodId = item->data(Qt::UserRole).toInt();
    restaurant.removeFood(foodId);
    QMessageBox::information(this, "Removed", "Food item removed.");
    refreshMenu();
}
