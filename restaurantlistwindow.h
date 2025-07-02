#ifndef RESTAURANTLISTWINDOW_H
#define RESTAURANTLISTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "clientnetwork.h"

class RestaurantListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantListWindow(ClientNetwork* net, QWidget* parent = nullptr);

private slots:
    void onRestaurantClicked(QListWidgetItem* item);
    void onMessageReceived(const QString& msg);

private:
    ClientNetwork* network;
    QListWidget* restaurantList;
    QMap<QString, int> nameToId;
};

#endif // RESTAURANTLISTWINDOW_H
