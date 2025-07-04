
#ifndef ORDERHISTORYWIDGET_H
#define ORDERHISTORYWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "ClientNetwork.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QListWidget>


class OrderHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrderHistoryWidget(ClientNetwork* net, const QString& username, QWidget *parent = nullptr);
   explicit OrderHistoryWidget(QWidget *parent = nullptr);
private slots:
    void refreshOrders();
    void onMessageReceived(const QString& msg);

private:
    ClientNetwork* network;
    QString username;

    QListWidget* orderList;
    QPushButton* refreshBtn;
QListWidget* listWidget;
    QVBoxLayout* layout;
    void loadOrders();
};

#endif // ORDERHISTORYWIDGET_H
