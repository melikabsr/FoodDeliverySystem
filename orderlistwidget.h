#ifndef ORDERLISTWIDGET_H
#define ORDERLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>

class OrderListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListWidget(QWidget *parent = nullptr);

private:
    QListWidget* listWidget;
};

#endif // ORDERLISTWIDGET_H

