#include "RestaurantAdminWidget.h"
#include "Restaurant.h"
#include "RestaurantService.h"
#include "AddRestaurantDialog.h"
#include <QMessageBox>

RestaurantAdminWidget::RestaurantAdminWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("🏢 Manage Restaurants");
    resize(500, 500);

    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("📋 لیست رستوران‌های موجود:");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(titleLabel);

    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);

    addBtn = new QPushButton("➕ Add Restaurant");
    removeBtn = new QPushButton("❌ Remove Selected");
    layout->addWidget(addBtn);
    layout->addWidget(removeBtn);

    connect(addBtn, &QPushButton::clicked, this, &RestaurantAdminWidget::onAddRestaurantClicked);
    connect(removeBtn, &QPushButton::clicked, this, &RestaurantAdminWidget::onRemoveSelectedClicked);

    refreshList();
}

void RestaurantAdminWidget::onAddRestaurantClicked()
{
    AddRestaurantDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshList();
    }
}

void RestaurantAdminWidget::onRemoveSelectedClicked()
{
    auto item = listWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "No Selection", "لطفاً یک رستوران را انتخاب کنید.");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    RestaurantService::instance().removeRestaurant(id);
    QMessageBox::information(this, "Removed", "رستوران با موفقیت حذف شد.");
    refreshList();
}

void RestaurantAdminWidget::refreshList()
{
    listWidget->clear();
    auto restaurants = RestaurantService::instance().getAllRestaurants();

    for (const auto& r : restaurants) {
        QString info = QString("🏠 %1 | 📍 %2").arg(r.getName(), r.getAddress());
        QListWidgetItem* item = new QListWidgetItem(info);
        item->setData(Qt::UserRole, r.getId());
        listWidget->addItem(item);
    }
}
