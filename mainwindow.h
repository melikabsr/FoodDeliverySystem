#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Restaurant.h"

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(const Restaurant& restaurant, QWidget *parent = nullptr);

signals:
    void foodAdded(const Food& food);

private:
    QVBoxLayout* layout;
    void loadMenu(const QList<Food>& menu);
};

#endif // MENUWIDGET_H
