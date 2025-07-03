
#ifndef RESTAURANTLISTWINDOW_H
#define RESTAURANTLISTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>
#include "clientnetwork.h"
#include "Food.h"
class RestaurantListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantListWindow(ClientNetwork* net, QWidget* parent = nullptr);

private slots:
    void onRestaurantClicked(QListWidgetItem* item);
    void onMessageReceived(const QString& msg);

private:
    int pendingRestaurantId; // تعریفش رو به صورت private int توی کلاس اضافه کن
   QList<Food> parseMenuFromString(const QString& data);
    ClientNetwork* network;
    QListWidget* restaurantList;
    QMap<QString, int> nameToId;
    QString pendingRestaurantName;

   // QList<Food> parseMenuFromString(const QString& data);
};

#endif // RESTAURANTLISTWINDOW_H
