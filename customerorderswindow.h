#ifndef CUSTOMERORDERSWINDOW_H
#define CUSTOMERORDERSWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ClientNetwork.h"

class CustomerOrdersWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerOrdersWindow(const QString& username, ClientNetwork* network, QWidget* parent = nullptr);

private slots:
    void handleOrderResponse(const QString& message);

private:
    QString customerUsername;
    ClientNetwork* clientNetwork;
    QVBoxLayout* mainLayout;
    QScrollArea* scrollArea;
};

#endif // CUSTOMERORDERSWINDOW_H
