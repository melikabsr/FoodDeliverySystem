
#ifndef SERVERORDER_H
#define SERVERORDER_H

#include <QString>
#include <QList>
#include <QPair>
#include "Food.h"

class ServerOrder {
public:
    ServerOrder(int id, const QString& username);

    int getId() const;
    QString getCustomerUsername() const;
    void addItem(const Food& food, int quantity);
    QList<QPair<Food, int>> getItems() const;
    double getTotalAmount() const;

private:
    int orderId;
    QString customerUsername;
    QList<QPair<Food, int>> items;
};

#endif // SERVERORDER_H
