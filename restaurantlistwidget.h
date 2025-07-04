#ifndef RESTAURANTLISTWIDGET_H
#define RESTAURANTLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include "ClientNetwork.h"

class RestaurantListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantListWidget(ClientNetwork* network, const QString& username, QWidget* parent = nullptr);
    void closeEvent(QCloseEvent* event);
private slots:
    void onMessageReceived(const QString& msg);
    void onRestaurantSelected(QListWidgetItem* item);

private:
    ClientNetwork* network;
    QString username;

    QListWidget* listWidget;
    QMap<QListWidgetItem*, int> itemToId;
};

#endif // RESTAURANTLISTWIDGET_H
