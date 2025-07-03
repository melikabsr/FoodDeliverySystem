#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include "Food.h"

class QLabel;
class QPushButton;

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(const QString& restaurantName, const QList<Food>& menu, QWidget* parent = nullptr);

signals:
    void foodAdded(const Food& food);
    void foodRemoved(const Food& food);

private:
    QVBoxLayout* layout;
    QMap<int, QLabel*> quantityLabels;

    void loadMenu(const QList<Food>& menu);
    void updateQuantityLabel(int foodId, int quantity);
};

#endif // MENUWIDGET_H
