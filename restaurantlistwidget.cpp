#include "RestaurantListWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "MenuWindow.h"
#include <QCloseEvent>

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
    if (!itemToId.contains(item)) return;

    int id = itemToId.value(item);
    QString name = item->text().remove("🍽️ ").trimmed();

    auto* menuWindow = new MenuWindow(network, id, name, this);
    menuWindow->setAttribute(Qt::WA_DeleteOnClose);
    menuWindow->show();
}



void RestaurantListWidget::closeEvent(QCloseEvent* event)
{
    disconnect(network, &ClientNetwork::messageReceived, this, nullptr);
    QWidget::closeEvent(event);
}
