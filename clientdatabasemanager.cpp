#include "ClientDatabaseManager.h"
#include <QDebug>

ClientDatabaseManager::ClientDatabaseManager(QObject* parent)
    : QObject(parent) {}

ClientDatabaseManager& ClientDatabaseManager::instance()
{
    static ClientDatabaseManager inst;
    return inst;
}

bool ClientDatabaseManager::openDatabase(const QString& dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qWarning() << "❌ Cannot open client DB:" << db.lastError().text();
        return false;
    }

    qDebug() << "✅ Client database opened.";
    return true;
}

QSqlDatabase ClientDatabaseManager::getDatabase() const
{
    return db;
}

void ClientDatabaseManager::setupTables()
{
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS orders ("
               "id INTEGER PRIMARY KEY,"
               "status TEXT,"
               "total REAL,"
               "items TEXT,"
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");

    // در صورت نیاز به کش منو یا کاربران هم اضافه می‌کنیم
}





void ClientDatabaseManager::storeOrder(int id, const QString& status, double total, const QString& items)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO orders (id, status, total, items) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(status);
    query.addBindValue(total);
    query.addBindValue(items);

    if (!query.exec()) {
        qWarning() << "❌ Failed to insert order:" << query.lastError().text();
    } else {
        qDebug() << "✅ Order stored locally. ID:" << id;
    }
}





QList<QMap<QString, QVariant>> ClientDatabaseManager::getAllOrders()
{
    QList<QMap<QString, QVariant>> orders;
    QSqlQuery query("SELECT id, status, total, items FROM orders", db);

    while (query.next()) {
        QMap<QString, QVariant> order;
        order["id"] = query.value(0);
        order["status"] = query.value(1);
        order["total"] = query.value(2);
        order["items"] = query.value(3);
        orders.append(order);
    }

    return orders;
}


bool ClientDatabaseManager::orderExists(int id)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM orders WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

void ClientDatabaseManager::saveOrder(int id, const QString& status, double total, const QString& items)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO orders (id, status, total, items) VALUES (:id, :status, :total, :items)");
    query.bindValue(":id", id);
    query.bindValue(":status", status);
    query.bindValue(":total", total);
    query.bindValue(":items", items);
    if (!query.exec()) {
        qWarning() << "❌ Failed to save order:" << query.lastError().text();
    } else {
        qDebug() << "✅ Order saved to local DB:" << id;
    }
}
