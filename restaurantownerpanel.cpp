// #include "RestaurantOwnerPanel.h"
// #include <QMessageBox>
// #include <QApplication>
// #include "AddFoodDialog.h"
// #include "OrderManager.h"
// #include <QGroupBox>
// #include <QVBoxLayout>
// #include <QPushButton>
// #include <QLabel>

// // RestaurantOwnerPanel::RestaurantOwnerPanel(QWidget *parent)
// //     : QWidget(parent)
// // {
// //     QVBoxLayout* layout = new QVBoxLayout(this);

// //     welcomeLabel = new QLabel("👨‍🍳 Welcome, dear Restaurant Owner!", this);
// //     welcomeLabel->setAlignment(Qt::AlignCenter);

// //     viewMenuButton = new QPushButton("📋 View My Menu");
// //     addFoodButton = new QPushButton("➕ Add New Food");
// //     viewOrdersButton = new QPushButton("📦 View Orders");
// //     logoutButton = new QPushButton("Logout");

// //     layout->addWidget(welcomeLabel);
// //     layout->addWidget(viewMenuButton);
// //     layout->addWidget(addFoodButton);
// //     layout->addWidget(viewOrdersButton);
// //     layout->addWidget(logoutButton);

// //     // TODO: اتصال به صفحات مختلف - فعلاً فقط پیام ساده می‌دهیم
// //     connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
// //     connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
// //     connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
// //     connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
// // }

// void RestaurantOwnerPanel::showMenu()
// {
//     QWidget* menuWindow = new QWidget();
//     menuWindow->setWindowTitle("📋 My Menu");
//     menuWindow->resize(400, 500);

//     QVBoxLayout* layout = new QVBoxLayout(menuWindow);

//     if (myMenu.isEmpty()) {
//         layout->addWidget(new QLabel("❌ No food in menu."));
//     } else {
//         for (int i = 0; i < myMenu.size(); ++i) {
//             const Food& food = myMenu[i];

//             QGroupBox* box = new QGroupBox(food.getName());
//             QVBoxLayout* vbox = new QVBoxLayout(box);

//             QLabel* desc = new QLabel("📝 " + food.getDescription());
//             QLabel* price = new QLabel(QString("💰 %1 $").arg(food.getPrice()));
//             QPushButton* removeBtn = new QPushButton("🗑 Remove");

//             connect(removeBtn, &QPushButton::clicked, [=]() {
//                 myMenu.removeAt(i);
//                 box->hide();  // فقط همین کارت حذف میشه
//             });

//             vbox->addWidget(desc);
//             vbox->addWidget(price);
//             vbox->addWidget(removeBtn);
//             layout->addWidget(box);
//         }
//     }

//     menuWindow->setLayout(layout);
//     menuWindow->show();
// }


// void RestaurantOwnerPanel::addFood()
// {
//     AddFoodDialog dialog(this);
//     if (dialog.exec() == QDialog::Accepted) {
//         Food food = dialog.getNewFood();
//         myMenu.append(food);

//         QMessageBox::information(this, "Food Added",
//                                  QString("✅ %1 added to your menu!").arg(food.getName()));
//     }
// }

// void RestaurantOwnerPanel::viewOrders()
// {
//     QWidget* orderWindow = new QWidget();
//     orderWindow->setWindowTitle("📦 Orders for Your Restaurant");
//     orderWindow->resize(500, 500);

//     QVBoxLayout* layout = new QVBoxLayout(orderWindow);
//     QVector<Order> allOrders = OrderManager::instance().getAllOrders();

//     int matchCount = 0;

//     for (const Order& order : allOrders) {
//         bool hasMyFood = false;
//         for (const auto& pair : order.getItems()) {
//             const Food& orderedFood = pair.first;
//             for (const Food& myFood : myMenu) {
//                 if (orderedFood.getId() == myFood.getId()) {
//                     hasMyFood = true;
//                     break;
//                 }
//             }
//             if (hasMyFood) break;
//         }

//         if (hasMyFood) {
//             QGroupBox* box = new QGroupBox(QString("🧾 Order #%1 - Customer: %2")
//                                                .arg(order.getId()).arg(order.getCustomerUsername()));
//             QVBoxLayout* boxLayout = new QVBoxLayout(box);

//             boxLayout->addWidget(new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus()))));
//             boxLayout->addWidget(new QLabel(QString("Total: $%1").arg(order.getTotalAmount())));

//             for (const auto& pair : order.getItems()) {
//                 const Food& food = pair.first;
//                 int qty = pair.second;
//                 QLabel* label = new QLabel(QString("🍽️ %1 x %2").arg(food.getName()).arg(qty));
//                 boxLayout->addWidget(label);
//             }

//             layout->addWidget(box);
//             matchCount++;
//         }
//     }

//     if (matchCount == 0) {
//         layout->addWidget(new QLabel("❌ No matching orders for your food."));
//     }

//     orderWindow->setLayout(layout);
//     orderWindow->show();
// }

// void RestaurantOwnerPanel::logout()
// {
//     QMessageBox::information(this, "Logout", "خروج از پنل.");
//     qApp->exit();
// }




// RestaurantOwnerPanel::RestaurantOwnerPanel(ClientNetwork* net, QWidget *parent)
//     : QWidget(parent), network(net)
// {
//     welcomeLabel = new QLabel("👨‍🍳 Welcome, dear Restaurant Owner!", this);
//     viewMenuButton = new QPushButton("📋 View My Menu");
//     addFoodButton = new QPushButton("➕ Add New Food");
//     viewOrdersButton = new QPushButton("📦 View Orders");
//     logoutButton = new QPushButton("Logout");

//     QVBoxLayout* layout = new QVBoxLayout(this);
//     layout->addWidget(welcomeLabel);
//     layout->addWidget(viewMenuButton);
//     layout->addWidget(addFoodButton);
//     layout->addWidget(viewOrdersButton);
//     layout->addWidget(logoutButton);

//     connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
//     connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
//     connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
//     connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
// }
// #include "RestaurantOwnerPanel.h"
// #include <QMessageBox>
// #include <QApplication>
// #include "AddFoodDialog.h"
// #include "OrderManager.h"
// #include <QGroupBox>
// #include <QVBoxLayout>
// #include <QPushButton>
// #include <QLabel>
// #include "ClientNetwork.h"

// RestaurantOwnerPanel::RestaurantOwnerPanel(ClientNetwork* network, int restaurantId, QWidget* parent)
//     : QWidget(parent), clientNetwork(network), restaurantId(restaurantId)
// {
//     welcomeLabel = new QLabel("👨‍🍳 Welcome, dear Restaurant Owner!", this);
//     viewMenuButton = new QPushButton("📋 View My Menu");
//     addFoodButton = new QPushButton("➕ Add New Food");
//     viewOrdersButton = new QPushButton("📦 View Orders");
//     logoutButton = new QPushButton("Logout");

//     QVBoxLayout* layout = new QVBoxLayout(this);
//     layout->addWidget(welcomeLabel);
//     layout->addWidget(viewMenuButton);
//     layout->addWidget(addFoodButton);
//     layout->addWidget(viewOrdersButton);
//     layout->addWidget(logoutButton);

//     connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
//     connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
//     connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
//     connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
//     connect(clientNetwork, &ClientNetwork::menuReceived, this, &RestaurantOwnerPanel::updateMenuDisplay);

// }

// // void RestaurantOwnerPanel::showMenu()
// // {
// //     QWidget* menuWindow = new QWidget();
// //     menuWindow->setWindowTitle("📋 My Menu");
// //     menuWindow->resize(400, 500);

// //     QVBoxLayout* layout = new QVBoxLayout(menuWindow);

// //     if (myMenu.isEmpty()) {
// //         layout->addWidget(new QLabel("❌ No food in menu."));
// //     } else {
// //         for (int i = 0; i < myMenu.size(); ++i) {
// //             const Food& food = myMenu[i];

// //             QGroupBox* box = new QGroupBox(food.getName());
// //             QVBoxLayout* vbox = new QVBoxLayout(box);

// //             QLabel* desc = new QLabel("📝 " + food.getDescription());
// //             QLabel* price = new QLabel(QString("💰 %1 $").arg(food.getPrice()));
// //             QPushButton* removeBtn = new QPushButton("🗑 Remove");

// //             connect(removeBtn, &QPushButton::clicked, [=]() {
// //                 myMenu.removeAt(i);
// //                 box->hide();
// //             });

// //             vbox->addWidget(desc);
// //             vbox->addWidget(price);
// //             vbox->addWidget(removeBtn);
// //             layout->addWidget(box);
// //         }
// //     }

// //     menuWindow->setLayout(layout);
// //     menuWindow->show();
// // }

// void RestaurantOwnerPanel::addFood()
// {
//     AddFoodDialog dialog(this);
//     if (dialog.exec() == QDialog::Accepted) {
//         Food food = dialog.getNewFood();
//         myMenu.append(food);

//         // ارسال پیام به سرور برای ذخیره غذا
//         QString msg = QString("ADD_FOOD|%1~%2~%3~%4")
//                           .arg(food.getId())
//                           .arg(food.getName())
//                           .arg(food.getDescription())
//                           .arg(food.getPrice());
//         if (clientNetwork) {
//             network->sendMessage(msg);
//         }

//         QMessageBox::information(this, "Food Added",
//                                  QString("✅ %1 added to your menu and sent to server!").arg(food.getName()));
//     }
// }

// void RestaurantOwnerPanel::viewOrders()
// {
//     QWidget* orderWindow = new QWidget();
//     orderWindow->setWindowTitle("📦 Orders for Your Restaurant");
//     orderWindow->resize(500, 500);

//     QVBoxLayout* layout = new QVBoxLayout(orderWindow);
//     QVector<Order> allOrders = OrderManager::instance().getAllOrders();

//     int matchCount = 0;

//     for (const Order& order : allOrders) {
//         bool hasMyFood = false;
//         for (const auto& pair : order.getItems()) {
//             const Food& orderedFood = pair.first;
//             for (const Food& myFood : myMenu) {
//                 if (orderedFood.getId() == myFood.getId()) {
//                     hasMyFood = true;
//                     break;
//                 }
//             }
//             if (hasMyFood) break;
//         }

//         if (hasMyFood) {
//             QGroupBox* box = new QGroupBox(QString("🗓 Order #%1 - Customer: %2")
//                                                .arg(order.getId()).arg(order.getCustomerUsername()));
//             QVBoxLayout* boxLayout = new QVBoxLayout(box);

//             boxLayout->addWidget(new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus()))));
//             boxLayout->addWidget(new QLabel(QString("Total: $%1").arg(order.getTotalAmount())));

//             for (const auto& pair : order.getItems()) {
//                 const Food& food = pair.first;
//                 int qty = pair.second;
//                 QLabel* label = new QLabel(QString("🍽️ %1 x %2").arg(food.getName()).arg(qty));
//                 boxLayout->addWidget(label);
//             }

//             layout->addWidget(box);
//             matchCount++;
//         }
//     }

//     if (matchCount == 0) {
//         layout->addWidget(new QLabel("❌ No matching orders for your food."));
//     }

//     orderWindow->setLayout(layout);
//     orderWindow->show();
// }

// void RestaurantOwnerPanel::logout()
// {
//     QMessageBox::information(this, "Logout", "خروج از پنل.");
//     qApp->exit();
// }





// void RestaurantOwnerPanel::showMenu()
// {
//     if (!clientNetwork) return;

//     // بستن پنجره قبلی در صورت وجود
//     if (menuWindow) {
//         menuWindow->close();
//         delete menuWindow;
//         menuWindow = nullptr;
//     }

//     // ارسال درخواست منو به سرور
//     QString request = "GET_MY_MENU|" + QString::number(restaurantId);
//     clientNetwork->sendMessage(request);

//     // ساخت پنجره منو
//     menuWindow = new QWidget();
//     menuWindow->setWindowTitle("📋 My Menu");
//     menuWindow->setMinimumSize(500, 600);
//     menuWindow->setStyleSheet("background-color: #f9f9f9;");

//     menuLayout = new QVBoxLayout(menuWindow);

//     QLabel* loadingLabel = new QLabel("⏳ Loading menu...");
//     loadingLabel->setAlignment(Qt::AlignCenter);
//     loadingLabel->setStyleSheet("font-size: 16px; color: gray;");
//     menuLayout->addWidget(loadingLabel);

//     menuWindow->setLayout(menuLayout);
//     menuWindow->show();
// }



// void RestaurantOwnerPanel::updateMenuDisplay(const QList<Food>& menu)
// {
//     myMenu = menu;

//     if (!menuLayout) return;

//     // پاک‌سازی محتوای قبلی
//     QLayoutItem* item;
//     while ((item = menuLayout->takeAt(0)) != nullptr) {
//         delete item->widget();
//         delete item;
//     }

//     if (myMenu.isEmpty()) {
//         menuLayout->addWidget(new QLabel("❌ No food in menu."));
//     } else {
//         for (int i = 0; i < myMenu.size(); ++i) {
//             const Food& food = myMenu[i];

//             QGroupBox* box = new QGroupBox(food.getName());
//             QVBoxLayout* vbox = new QVBoxLayout(box);

//             QLabel* desc = new QLabel("📝 " + food.getDescription());
//             QLabel* price = new QLabel(QString("💰 %1 $").arg(food.getPrice()));
//             QPushButton* removeBtn = new QPushButton("🗑 Remove");

//             connect(removeBtn, &QPushButton::clicked, this, [=]() {
//                 // اینجا به جای حذف محلی، در مرحله بعد پیام به سرور ارسال می‌شود
//                 removeFoodFromMenu(food.getId(), box);
//             });

//             vbox->addWidget(desc);
//             vbox->addWidget(price);
//             vbox->addWidget(removeBtn);
//             menuLayout->addWidget(box);
//         }
//     }
// }

// void RestaurantOwnerPanel::removeFoodFromMenu(int foodId, QGroupBox* boxToRemove)
// {
//     if (!clientNetwork) return;

//     QString msg = "REMOVE_FOOD|" + QString::number(foodId);
//     clientNetwork->sendMessage(msg);

//     // برای تست اولیه می‌تونی مستقیماً حذف بصری انجام بدی:
//     if (boxToRemove) boxToRemove->hide();

//     // اما در مرحله ۲ پاسخ سرور بررسی خواهد شد
// }


#include "RestaurantOwnerPanel.h"
#include <QApplication>
#include "AddFoodDialog.h"
#include "OrderManager.h"
#include "RestaurantOrdersWindow.h"
#include <QMessageBox>
#include "ClientDatabaseManager.h"
#include "MainWindow.h"
RestaurantOwnerPanel::RestaurantOwnerPanel(ClientNetwork* network, int restaurantId, QWidget* parent)
    : QWidget(parent), clientNetwork(network), restaurantId(restaurantId)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("👨‍🍳 Welcome, dear Restaurant Owner!", this);
    layout->addWidget(welcomeLabel);

    ordersTextEdit = new QTextEdit(this);
    ordersTextEdit->setReadOnly(true);
    layout->addWidget(ordersTextEdit);

    viewMenuButton = new QPushButton("📋 View My Menu");
    addFoodButton = new QPushButton("➕ Add New Food");
    viewOrdersButton = new QPushButton("📦 View Orders");
    logoutButton = new QPushButton("🚪 Logout");

    layout->addWidget(viewMenuButton);
    layout->addWidget(addFoodButton);
    layout->addWidget(viewOrdersButton);
    layout->addWidget(logoutButton);

    // اتصال سیگنال‌ها
    connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
    connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
    connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
    connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
    connect(clientNetwork, &ClientNetwork::menuReceived, this, &RestaurantOwnerPanel::updateMenuDisplay);
}


void RestaurantOwnerPanel::showMenu()
{
    if (!clientNetwork) return;
    if (menuWindow) { menuWindow->close(); delete menuWindow; menuWindow = nullptr; }

    QString request = "GET_MY_MENU|" + QString::number(restaurantId);
    clientNetwork->sendMessage(request);

    menuWindow = new QWidget();
    menuWindow->setWindowTitle("\xf0\x9f\x93\x8b My Menu");
    menuWindow->setMinimumSize(500, 600);
    menuWindow->setStyleSheet("background-color: #f9f9f9;");

    menuLayout = new QVBoxLayout(menuWindow);
    QLabel* loadingLabel = new QLabel("\xe2\x8f\xb3 Loading menu...");
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingLabel->setStyleSheet("font-size: 16px; color: gray;");
    menuLayout->addWidget(loadingLabel);

    menuWindow->setLayout(menuLayout);
    menuWindow->show();
}

void RestaurantOwnerPanel::updateMenuDisplay(const QList<Food>& menu)
{
    myMenu = menu;
    if (!menuLayout) return;

    QLayoutItem* item;
    while ((item = menuLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (myMenu.isEmpty()) {
        menuLayout->addWidget(new QLabel("\xe2\x9d\x8c No food in menu."));
    } else {
        for (const Food& food : myMenu) {
            QGroupBox* box = new QGroupBox(food.getName());
            QVBoxLayout* vbox = new QVBoxLayout(box);

            QLabel* desc = new QLabel("\xf0\x9f\x93\x9d " + food.getDescription());
            QLabel* price = new QLabel(QString("\xf0\x9f\x92\xb0 %1 $").arg(food.getPrice()));
            QPushButton* removeBtn = new QPushButton("\xf0\x9f\x97\x91 Remove");

            connect(removeBtn, &QPushButton::clicked, this, [=]() {
                removeFoodFromMenu(food.getId(), box);
            });

            vbox->addWidget(desc);
            vbox->addWidget(price);
            vbox->addWidget(removeBtn);
            menuLayout->addWidget(box);
        }
    }
}

void RestaurantOwnerPanel::addFood()
{
    AddFoodDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Food food = dialog.getNewFood();
        myMenu.append(food);

        QString msg = QString("ADD_FOOD|%1~%2~%3~%4")
                          .arg(food.getId())
                          .arg(food.getName())
                          .arg(food.getDescription())
                          .arg(food.getPrice());
        if (clientNetwork) {
            clientNetwork->sendMessage(msg);
        }

        QMessageBox::information(this, "Food Added",
                                 QString("\xe2\x9c\x85 %1 added to your menu and sent to server!").arg(food.getName()));
    }
}

void RestaurantOwnerPanel::viewOrders()
{


    RestaurantOrdersWindow* win = new RestaurantOrdersWindow(restaurantId, clientNetwork);
    win->show();
//    // QWidget* orderWindow = new QWidget();
//      RestaurantOrdersWindow* win = new RestaurantOrdersWindow(restaurantId, clientNetwork);

//     orderWindow->setWindowTitle("\xf0\x9f\x93\xa6 Orders for Your Restaurant");
//     orderWindow->resize(500, 500);

//     QVBoxLayout* layout = new QVBoxLayout(orderWindow);
//     QVector<Order> allOrders = OrderManager::instance().getAllOrders();
//     int matchCount = 0;

//     for (const Order& order : allOrders) {
//         bool hasMyFood = false;
//         for (const auto& pair : order.getItems()) {
//             const Food& orderedFood = pair.first;
//             for (const Food& myFood : myMenu) {
//                 if (orderedFood.getId() == myFood.getId()) {
//                     hasMyFood = true;
//                     break;
//                 }
//             }
//             if (hasMyFood) break;
//         }

//         if (hasMyFood) {
//             QGroupBox* box = new QGroupBox(QString("\xf0\x9f\x97\x93 Order #%1 - Customer: %2")
//                                                .arg(order.getId()).arg(order.getCustomerUsername()));
//             QVBoxLayout* boxLayout = new QVBoxLayout(box);

//             boxLayout->addWidget(new QLabel(QString("Status: %1").arg(static_cast<int>(order.getStatus()))));
//             boxLayout->addWidget(new QLabel(QString("Total: $%1").arg(order.getTotalAmount())));

//             for (const auto& pair : order.getItems()) {
//                 const Food& food = pair.first;
//                 int qty = pair.second;
//                 QLabel* label = new QLabel(QString("\xf0\x9f\x8d\xbd %1 x %2").arg(food.getName()).arg(qty));
//                 boxLayout->addWidget(label);
//             }

//             layout->addWidget(box);
//             matchCount++;
//         }
//     }

//     if (matchCount == 0) {
//         layout->addWidget(new QLabel("\xe2\x9d\x8c No matching orders for your food."));
//     }

//     orderWindow->setLayout(layout);
//    // orderWindow->show();
//     win->show();

// }

// void RestaurantOwnerPanel::logout()
// {
//     QMessageBox::information(this, "Logout", "خروج از پنل.");
//     qApp->exit();
}

void RestaurantOwnerPanel::removeFoodFromMenu(int foodId, QGroupBox* boxToRemove)
{
    if (!clientNetwork) return;

    QString msg = "REMOVE_FOOD|" + QString::number(foodId);
    clientNetwork->sendMessage(msg);

    if (boxToRemove) boxToRemove->hide();
}






void RestaurantOwnerPanel::refreshOrders()
{
    ordersTextEdit->clear();  // یا هر ویجت نمایشی دیگر
    QList<QMap<QString, QVariant>> orders = ClientDatabaseManager::instance().getAllOrders();
    for (const auto& order : orders) {
        QString line = QString("سفارش #%1\nوضعیت: %2\nجمع کل: %3 تومان\nاقلام: %4\n---")
                           .arg(order["id"].toInt())
                           .arg(order["status"].toString())
                           .arg(order["total"].toDouble())
                           .arg(order["items"].toString());
        ordersTextEdit->append(line);
    }
}


void RestaurantOwnerPanel::logout()
{
    QMessageBox::information(this, "Logout", "با موفقیت خارج شدید.");

    QWidget* parent = this->parentWidget();
    while (parent && !qobject_cast<MainWindow*>(parent)) {
        parent = parent->parentWidget();
    }

    if (MainWindow* mainWin = qobject_cast<MainWindow*>(parent)) {
        mainWin->showWelcomeScreen();  //  بازگشت به صفحه‌ی خوش‌آمدگویی
    }

    this->deleteLater();
}

