#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "ClientNetwork.h"

class CustomerPanel : public QWidget {
    Q_OBJECT

public:
    explicit CustomerPanel(ClientNetwork* net, const QString& username, QWidget* parent = nullptr);
    void refreshOrders();

private slots:
    void showOrderHistory();

private:
    ClientNetwork* network;
    QString username;
    QLabel* welcomeLabel;
    QLabel* statusLabel;
    QVBoxLayout* mainLayout;
    QListWidget* orderListWidget;
    QPushButton *viewRestaurantsButton, *viewCartButton, *viewOrdersButton, *logoutButton;
};

#endif // CUSTOMERPANEL_H

