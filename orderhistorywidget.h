#ifndef ORDERHISTORYWIDGET_H
#define ORDERHISTORYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include "OrderManager.h"
#include "CustomerService.h"

class OrderHistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderHistoryWidget(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;
    void loadOrders();
};

#endif // ORDERHISTORYWIDGET_H
