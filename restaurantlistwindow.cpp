#include "restaurantlistwindow.h"
#include "menuwindow.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

RestaurantListWindow::RestaurantListWindow(ClientNetwork* net, QWidget* parent)
    : QWidget(parent), network(net)
{
    setWindowTitle("🍴 Restaurant List");
    resize(400, 400);

    restaurantList = new QListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(restaurantList);

    connect(restaurantList, &QListWidget::itemClicked, this, &RestaurantListWindow::onRestaurantClicked);
    connect(network, &ClientNetwork::messageReceived, this, &RestaurantListWindow::onMessageReceived);

    // درخواست لیست رستوران‌ها از سرور
    network->sendMessage("GET_RESTAURANTS");
}

void RestaurantListWindow::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("RESTAURANTS|")) return;

    QString data = msg.section("|", 1);
    QStringList rows = data.split(";");

    for (const QString& row : rows) {
        QStringList cols = row.split(",");
        if (cols.size() < 3) continue;

        int id = cols[0].toInt();
        QString name = cols[1];
        QString address = cols[2];
        QString display = QString("%1 (%2)").arg(name, address);

        nameToId.insert(display, id);
        restaurantList->addItem(display);
    }
}

void RestaurantListWindow::onRestaurantClicked(QListWidgetItem* item)
{
    QString name = item->text();
    if (!nameToId.contains(name)) return;

    int id = nameToId.value(name);
    network->sendMessage(QString("GET_MENU|%1").arg(id));

    auto* menuWin = new MenuWindow(network, id, name);
    menuWin->show();
}
