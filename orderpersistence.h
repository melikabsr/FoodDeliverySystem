#ifndef ORDERPERSISTENCE_H
#define ORDERPERSISTENCE_H

#include "ServerOrder.h"
#include <QVector>

class OrderPersistence {
public:
    static bool saveOrderToDatabase(const ServerOrder& order);
    static QVector<ServerOrder> loadOrdersForCustomer(const QString& username);
    static ServerOrder* loadOrderById(int orderId);
    static int loadMaxOrderId(); // برای ادامه شمارنده
};

#endif // ORDERPERSISTENCE_H
