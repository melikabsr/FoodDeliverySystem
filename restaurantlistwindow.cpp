



#include "restaurantlistwindow.h"
#include "menuwidget.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>

RestaurantListWindow::RestaurantListWindow(ClientNetwork* network, QWidget* parent)
    : QWidget(parent), network(network)
{
    setWindowTitle("🍴 Restaurant List");
    resize(400, 400);

    restaurantList = new QListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("🍽️ Select a restaurant:"));
    layout->addWidget(restaurantList);

    setLayout(layout);

    connect(restaurantList, &QListWidget::itemClicked, this, &RestaurantListWindow::onRestaurantClicked);
    connect(network, &ClientNetwork::messageReceived, this, &RestaurantListWindow::onMessageReceived);

    network->sendMessage("GET_RESTAURANTS");
}
void RestaurantListWindow::onMessageReceived(const QString& msg)
{
    if (msg.startsWith("RESTAURANTS|")) {
        QString data = msg.section("|", 1);
        QStringList rows = data.split(";", Qt::SkipEmptyParts);

        restaurantList->clear();

        for (const QString& row : rows) {
            QStringList cols = row.split(",");
            if (cols.size() < 2) continue;

            QString name = cols[1].trimmed();
            QString address = cols.size() >= 3 ? cols[2].trimmed() : "No address";

            QString display = QString("%1 (%2)").arg(name, address);
            QListWidgetItem* item = new QListWidgetItem(display);
            restaurantList->addItem(item);
        }
    }
    else if (msg.startsWith("MENU|")) {
        QString data = msg.section("|", 1);
        QList<Food> menu = parseMenuFromString(data);

        if (!pendingRestaurantName.isEmpty()) {
            auto* menuWin = new MenuWidget(pendingRestaurantName, menu);
            menuWin->setAttribute(Qt::WA_DeleteOnClose);
            menuWin->show();
        }
    }
}

void RestaurantListWindow::onRestaurantClicked(QListWidgetItem* item)
{
    QString displayName = item->text();

    // استخراج نام از داخل نمایش (مثل "Pizza Land (Valiasr St.)" → "Pizza Land")
    QString restaurantName = displayName.section(" (", 0, 0).trimmed();
    pendingRestaurantName = restaurantName;

    network->sendMessage(QString("GET_MENU|%1").arg(restaurantName));
}
QList<Food> RestaurantListWindow::parseMenuFromString(const QString& data)
{
    QList<Food> menu;
    QStringList items = data.split(";", Qt::SkipEmptyParts);

    for (const QString& item : items) {
        QStringList parts = item.split("~");
        if (parts.size() >= 4) {
            int id = parts[0].toInt();
            QString name = parts[1];
            QString desc = parts[2];
            double price = parts[3].toDouble();
            menu.append(Food(id, name, desc, price, FoodCategory::FAST_FOOD, ""));
        }
    }

    return menu;
}
