#ifndef ORDERHISTORYWINDOW_H
#define ORDERHISTORYWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "clientnetwork.h"

class OrderHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderHistoryWindow(ClientNetwork* net, const QString& username, QWidget* parent = nullptr);

private slots:
    void onMessageReceived(const QString& msg);

private:
    ClientNetwork* network;
    QString user;
    QListWidget* listWidget;
     QListWidget* list;
};

#endif // ORDERHISTORYWINDOW_H
