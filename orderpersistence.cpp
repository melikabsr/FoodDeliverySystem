#include "OrderPersistence.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include "serverorder.h"
bool OrderPersistence::saveOrderToDatabase(const ServerOrder& order)
{
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("INSERT INTO orders (id, customer_username, status, timestamp) VALUES (?, ?, ?, ?)");
    query.addBindValue(order.getId());
    query.addBindValue(order.getCustomerUsername());
    query.addBindValue(ServerOrder::statusToString(order.getStatus()));

    query.addBindValue(order.getTimestamp().toString(Qt::ISODate));

    if (!query.exec()) {
        qWarning() << "❌ Failed to insert order:" << query.lastError().text();
        return false;
    }

    for (const auto& pair : order.getItems()) {
        QSqlQuery itemQuery(db);
        itemQuery.prepare("INSERT INTO order_items (order_id, food_name, quantity, price) VALUES (?, ?, ?, ?)");
        itemQuery.addBindValue(order.getId());
        itemQuery.addBindValue(pair.first.getName());
        itemQuery.addBindValue(pair.second);
        itemQuery.addBindValue(pair.first.getPrice());

        if (!itemQuery.exec()) {
            qWarning() << "❌ Failed to insert order item:" << itemQuery.lastError().text();
            return false;
        }
    }

    return true;
}

QVector<ServerOrder> OrderPersistence::loadOrdersForCustomer(const QString& username)
{
    QVector<ServerOrder> result;
    QSqlDatabase db = DatabaseManager::instance().getDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id, status, timestamp FROM orders WHERE customer_username = ?");
    query.addBindValue(username);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString statusStr = query.value(1).toString();
            QDateTime ts = QDateTime::fromString(query.value(2).toString(), Qt::ISODate);

            ServerOrder order(id, username);
            order.setStatus(ServerOrder::fromString(statusStr));
            order.setTimestamp(ts);

            // لود آیتم‌ها
            QSqlQuery itemQuery(db);
            itemQuery.prepare("SELECT food_name, quantity, price FROM order_items WHERE order_id = ?");
            itemQuery.addBindValue(id);

            if (itemQuery.exec()) {
                while (itemQuery.next()) {
                    QString name = itemQuery.value(0).toString();
                    int qty = itemQuery.value(1).toInt();
                    double price = itemQuery.value(2).toDouble();
                    order.addItem(Food(0, name, "", price, FoodCategory::FAST_FOOD, ""), qty);
                }
            }

            result.append(order);
        }
    }

    return result;
}

int OrderPersistence::loadMaxOrderId()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    if (query.exec("SELECT MAX(id) FROM orders") && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
