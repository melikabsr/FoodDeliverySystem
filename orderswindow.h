// OrdersWindow.h
#pragma once

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class OrdersWindow : public QWidget
{
    Q_OBJECT

public:
    OrdersWindow(QWidget* parent = nullptr);

public slots:
    void refreshOrders();  // این تابع بعد از دریافت سفارش‌های جدید صدا زده میشه

private:
    QListWidget* orderList;
};
