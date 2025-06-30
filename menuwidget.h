#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "Restaurant.h"
#include "Food.h"
#include "enums.h"

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(const Restaurant& restaurant, QWidget *parent = nullptr);
    void loadMenu(const QList<Food>& menu);

signals:
    void foodAdded(const Food& food);

private:
    QVBoxLayout* layout;
};

#endif // MENUWIDGET_H

