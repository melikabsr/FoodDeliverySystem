
#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "OrderHistoryWidget.h"
#include "ClientNetwork.h"
#include <QListWidget>

class CustomerPanel : public QWidget
{
    Q_OBJECT

public:
   // explicit CustomerPanel(QWidget *parent = nullptr);
    explicit CustomerPanel(ClientNetwork* net, const QString& username, QWidget *parent = nullptr);
private slots:
    void showOrderHistory();

private:
    QLabel* welcomeLabel;
    QPushButton* viewRestaurantsButton;
    QPushButton* viewCartButton;
    QPushButton* viewOrdersButton;
    QPushButton* logoutButton;
    QPushButton* historyBtn ;

QVBoxLayout* mainLayout;
QListWidget* orderListWidget;

    ClientNetwork* network;
    QString username;
public slots:
    void refreshOrders();
};

#endif // CUSTOMERPANEL_H
