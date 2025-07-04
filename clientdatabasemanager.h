#ifndef CLIENTDATABASEMANAGER_H
#define CLIENTDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class ClientDatabaseManager : public QObject
{
    Q_OBJECT

public:
    static ClientDatabaseManager& instance();
    bool openDatabase(const QString& dbName = "client.db");
    void setupTables();
    QSqlDatabase getDatabase() const;
    void storeOrder(int id, const QString& status, double total, const QString& items);
    QList<QMap<QString, QVariant>> getAllOrders();
    bool orderExists(int orderId);
    void saveOrder(int id, const QString& status, double total, const QString& items);


private:
    explicit ClientDatabaseManager(QObject* parent = nullptr);
    QSqlDatabase db;
};

#endif // CLIENTDATABASEMANAGER_H
