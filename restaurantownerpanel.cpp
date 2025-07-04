#include "RestaurantOwnerPanel.h"
#include "AddFoodDialog.h"
#include "RestaurantOrdersWindow.h"
#include "MainWindow.h"
#include <QMessageBox>
#include <QGroupBox>

RestaurantOwnerPanel::RestaurantOwnerPanel(ClientNetwork* network, int restaurantId, QWidget* parent)
    : QWidget(parent), clientNetwork(network), restaurantId(restaurantId)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("👨‍🍳 Welcome, Restaurant Owner!");
    layout->addWidget(welcomeLabel);

    ordersTextEdit = new QTextEdit(this);
    ordersTextEdit->setReadOnly(true);
    layout->addWidget(ordersTextEdit);

    viewMenuButton = new QPushButton("📋 View Menu");
    addFoodButton = new QPushButton("➕ Add Food");
    viewOrdersButton = new QPushButton("📦 View Orders");
    logoutButton = new QPushButton("🚪 Logout");

    layout->addWidget(viewMenuButton);
    layout->addWidget(addFoodButton);
    layout->addWidget(viewOrdersButton);
    layout->addWidget(logoutButton);

    connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::showMenu);
    connect(addFoodButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::addFood);
    connect(viewOrdersButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::viewOrders);
    connect(logoutButton, &QPushButton::clicked, this, &RestaurantOwnerPanel::logout);
    connect(clientNetwork, &ClientNetwork::menuReceived, this, &RestaurantOwnerPanel::updateMenuDisplay);
}

void RestaurantOwnerPanel::showMenu()
{
    if (menuWindow) {
        menuWindow->close();
        delete menuWindow;
    }

    menuWindow = new QWidget();
    menuWindow->setWindowTitle("📋 My Menu");
    menuLayout = new QVBoxLayout(menuWindow);
    menuWindow->setLayout(menuLayout);
    menuWindow->resize(500, 600);
    menuWindow->show();

    clientNetwork->sendMessage("GET_MY_MENU");
}

void RestaurantOwnerPanel::updateMenuDisplay(const QList<Food>& menu)
{
    myMenu = menu;

    QLayoutItem* item;
    while ((item = menuLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (const Food& food : myMenu) {
        QGroupBox* box = new QGroupBox(food.getName());
        QVBoxLayout* vbox = new QVBoxLayout(box);

        QLabel* desc = new QLabel(food.getDescription());
        QLabel* price = new QLabel(QString("💵 %1 $").arg(food.getPrice()));
        QPushButton* removeBtn = new QPushButton("🗑 Remove");

        connect(removeBtn, &QPushButton::clicked, this, [=]() {
            removeFoodFromMenu(food.getId(), box);
        });

        vbox->addWidget(desc);
        vbox->addWidget(price);
        vbox->addWidget(removeBtn);
        menuLayout->addWidget(box);
    }
}

void RestaurantOwnerPanel::addFood()
{
    AddFoodDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Food food = dialog.getNewFood();
        QString msg = QString("ADD_FOOD|%1|%2|%3|%4")
                          .arg(restaurantId)
                          .arg(food.getName())
                          .arg(food.getDescription())
                          .arg(food.getPrice());
        clientNetwork->sendMessage(msg);
        QMessageBox::information(this, "✅ Added", "Food sent to server.");
        clientNetwork->sendMessage("GET_MY_MENU");
    }
}

void RestaurantOwnerPanel::removeFoodFromMenu(int foodId, QGroupBox* box)
{
    QString msg = QString("REMOVE_FOOD|%1").arg(foodId);
    clientNetwork->sendMessage(msg);
    if (box) box->hide();
}

void RestaurantOwnerPanel::viewOrders()
{
    auto* ordersWin = new RestaurantOrdersWindow(restaurantId, clientNetwork);
    ordersWin->setAttribute(Qt::WA_DeleteOnClose);
    ordersWin->show();
}

void RestaurantOwnerPanel::refreshOrders()
{
    ordersTextEdit->clear();
    ordersTextEdit->append("📥 Orders will appear here when updated.");
}

void RestaurantOwnerPanel::logout()
{
    QMessageBox::information(this, "👋 Logout", "Logging out...");
    QWidget* parent = this->parentWidget();
    while (parent && !qobject_cast<MainWindow*>(parent)) {
        parent = parent->parentWidget();
    }

    if (MainWindow* mw = qobject_cast<MainWindow*>(parent)) {
        mw->showWelcomeScreen();
    }

    this->deleteLater();
}
