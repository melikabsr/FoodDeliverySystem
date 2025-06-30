#include "RestaurantOwnerPanel.h"
#include <QMessageBox>
#include <QApplication>
#include "AddFoodDialog.h"
#include "OrderManager.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

RestaurantOwnerPanel::RestaurantOwnerPanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("👨‍🍳 Welcome, dear Restaurant Owner!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    viewMenuButton = new QPushButton("📋 View My Menu");
    addFoodButton = new QPushButton("➕ Add New Food");
    viewOrdersButton = new QPushButton("📦 View Orders");
    logoutButton = new QPushButton("Logout");

    layout->addWidget(welcomeLabel);
    layout->addWidget(viewMenuButton);
    layout->addWidget(addFoodButton);
    layout->addWidget(viewOrdersButton);
    layout->addWidget(logoutButton);

    // TODO: اتصال به صفحات مختلف - فعلاً فقط پیام ساده می‌دهیم
    connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
    connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
    connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
    connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
}

void RestaurantOwnerPanel::showMenu()
{
    QWidget* menuWindow = new QWidget();
    menuWindow->setWindowTitle("📋 My Menu");
    menuWindow->resize(400, 500);

    QVBoxLayout* layout = new QVBoxLayout(menuWindow);

    if (myMenu.isEmpty()) {
        layout->addWidget(new QLabel("❌ No food in menu."));
    } else {
        for (int i = 0; i < myMenu.size(); ++i) {
            const Food& food = myMenu[i];

            QGroupBox* box = new QGroupBox(food.getName());
            QVBoxLayout* vbox = new QVBoxLayout(box);

            QLabel* desc = new QLabel("📝 " + food.getDescription());
            QLabel* price = new QLabel(QString("💰 %1 $").arg(food.getPrice()));
            QPushButton* removeBtn = new QPushButton("🗑 Remove");

            connect(removeBtn, &QPushButton::clicked, [=]() {
                myMenu.removeAt(i);
                box->hide();  // فقط همین کارت حذف میشه
            });

            vbox->addWidget(desc);
            vbox->addWidget(price);
            vbox->addWidget(removeBtn);
            layout->addWidget(box);
        }
    }

    menuWindow->setLayout(layout);
    menuWindow->show();
}


void RestaurantOwnerPanel::addFood()
{
    AddFoodDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Food food = dialog.getNewFood();
        myMenu.append(food);

        QMessageBox::information(this, "Food Added",
                                 QString("✅ %1 added to your menu!").arg(food.getName()));
    }
}

void RestaurantOwnerPanel::viewOrders()
{
    QWidget* orderWindow = new QWidget();
    orderWindow->setWindowTitle("📦 Orders for Your Restaurant");
    orderWindow->resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(orderWindow);
    QVector<Order> allOrders = OrderManager::instance().getAllOrders();

    int matchCount = 0;

    for (const Order& order : allOrders) {
        bool hasMyFood = false;
        for (const auto& pair : order.getItems()) {
            const Food& orderedFood = pair.first;
            for (const Food& myFood : myMenu) {
                if (orderedFood.getId() == myFood.getId()) {
                    hasMyFood = true;
                    break;
                }
            }
            if (hasMyFood) break;
        }

        if (hasMyFood) {
            QGroupBox* box = new QGroupBox(QString("🧾 Order #%1 - Customer: %2")
                                               .arg(order.getId()).arg(order.getCustomerUsername()));
            QVBoxLayout* boxLayout = new QVBoxLayout(box);

            boxLayout->addWidget(new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus()))));
            boxLayout->addWidget(new QLabel(QString("Total: $%1").arg(order.getTotalAmount())));

            for (const auto& pair : order.getItems()) {
                const Food& food = pair.first;
                int qty = pair.second;
                QLabel* label = new QLabel(QString("🍽️ %1 x %2").arg(food.getName()).arg(qty));
                boxLayout->addWidget(label);
            }

            layout->addWidget(box);
            matchCount++;
        }
    }

    if (matchCount == 0) {
        layout->addWidget(new QLabel("❌ No matching orders for your food."));
    }

    orderWindow->setLayout(layout);
    orderWindow->show();
}

void RestaurantOwnerPanel::logout()
{
    QMessageBox::information(this, "Logout", "خروج از پنل.");
    qApp->exit();
}
