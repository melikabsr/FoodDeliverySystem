#include "RestaurantListWidget.h"
#include <QGroupBox>
#include <QMessageBox>
#include <menuwidget.h>
#include "MenuWindow.h"
#include <QVBoxLayout>
#include <QLabel>

// RestaurantListWidget::RestaurantListWidget(QWidget *parent)
//     : QWidget(parent)
// {
//     mainLayout = new QVBoxLayout(this);
//     setLayout(mainLayout);

//     loadRestaurants();
//     displayRestaurants();
// }

RestaurantListWidget::RestaurantListWidget(ClientNetwork* network, const QString& username, QWidget* parent)
    : QWidget(parent), network(network), username(username)
{
    setWindowTitle("📋 Available Restaurants");
    resize(400, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(new QLabel("🍽️ Select a restaurant:"));
    layout->addWidget(listWidget);

    connect(network, &ClientNetwork::messageReceived, this, &RestaurantListWidget::onMessageReceived);
    connect(listWidget, &QListWidget::itemClicked, this, &RestaurantListWidget::onRestaurantSelected);

    network->sendMessage("GET_RESTAURANTS");
}




RestaurantListWidget::RestaurantListWidget(ClientNetwork* network, QWidget* parent)
    : QWidget(parent), network(network)
{
    setWindowTitle("📋 Available Restaurants");
    resize(400, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(new QLabel("🍽️ Select a restaurant:"));
    layout->addWidget(listWidget);

    connect(network, &ClientNetwork::messageReceived, this, &RestaurantListWidget::onMessageReceived);
    connect(listWidget, &QListWidget::itemClicked, this, &RestaurantListWidget::onRestaurantSelected);

    network->sendMessage("GET_RESTAURANTS");
}

void RestaurantListWidget::loadRestaurants()
{
    mockRestaurants.append(Restaurant(1, "Pizza House", "Main Street 101"));
    mockRestaurants.append(Restaurant(2, "Kebab City", "Vali-Asr Ave 55"));
    mockRestaurants.append(Restaurant(3, "Cafe Queen", "Shahrak Blvd 19"));
}

void RestaurantListWidget::displayRestaurants()
{
    for (const Restaurant& r : mockRestaurants) {
        QGroupBox* card = new QGroupBox(r.getName());
        QVBoxLayout* vbox = new QVBoxLayout(card);

        QLabel* addressLabel = new QLabel("📍 Address: " + r.getAddress());
        QPushButton* viewMenuBtn = new QPushButton("View Menu");

        vbox->addWidget(addressLabel);
        vbox->addWidget(viewMenuBtn);
        card->setLayout(vbox);

        mainLayout->addWidget(card);

        connect(viewMenuBtn, &QPushButton::clicked, [=]() {
            MenuWidget* menu = new MenuWidget(r.getName(), r.getMenu());
            menu->setWindowTitle("Menu - " + r.getName());
            menu->resize(400, 400);
            menu->show();
        });

    }
}





void RestaurantListWidget::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("RESTAURANTS|")) return;

    listWidget->clear();
    itemToId.clear();

    QString data = msg.section("|", 1);
    QStringList rows = data.split(";");

    for (const QString& row : rows) {
        QStringList cols = row.split(",");
        if (cols.size() < 2) continue;

        int id = cols[0].toInt();
        QString name = cols[1];

        QListWidgetItem* item = new QListWidgetItem("🍽️ " + name);
        listWidget->addItem(item);
        itemToId[item] = id;
    }
}

void RestaurantListWidget::onRestaurantSelected(QListWidgetItem* item)
{
    int id = itemToId.value(item);
    QString name = item->text().remove("🍽️ ").trimmed();

    auto* menu = new MenuWindow(network, id, name);
    menu->show();
}
