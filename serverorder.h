
#ifndef SERVERORDER_H
#define SERVERORDER_H

#include <QString>
#include <QList>
#include <QPair>
#include "Food.h"
#include "QDateTime.h"
enum class OrderStatus {
    PENDING_CONFIRMATION,
    CONFIRMED,
    PREPARING,
    READY,
    DELIVERED ,
    PENDING,
    CANCELLED

};

class ServerOrder {
public:
    ServerOrder(int id, const QString& username);
 static OrderStatus fromString(const QString& s);
    int getId() const;
    QString getCustomerUsername() const;
    void addItem(const Food& food, int quantity);
    QList<QPair<Food, int>> getItems() const;
    double getTotalAmount() const;


    OrderStatus getStatus() const;
    void setStatus(OrderStatus newStatus);
    QDateTime getTimestamp() const ;
    void setTimestamp(const QDateTime& t) ;
    QDateTime timestamp;
    static QString statusToString(OrderStatus status);

private:
    int orderId;
    QString customerUsername;
    QList<QPair<Food, int>> items;
    OrderStatus status;

};

#endif // SERVERORDER_H


