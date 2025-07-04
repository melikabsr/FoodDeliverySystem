
#ifndef RESTAURANTLISTWINDOW_H
#define RESTAURANTLISTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include "clientnetwork.h"
#include "Food.h"

class RestaurantListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantListWindow(ClientNetwork* network, QWidget* parent = nullptr);

private slots:
    void onMessageReceived(const QString& msg);
    void onRestaurantClicked(QListWidgetItem* item);

private:
    ClientNetwork* network;
    QListWidget* restaurantList;
    QMap<QString, int> nameToId;

    int pendingRestaurantId = -1;
    QString pendingRestaurantName;

    QList<Food> parseMenuFromString(const QString& data);
};

#endif // RESTAURANTLISTWINDOW_H
