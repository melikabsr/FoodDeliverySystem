#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject* parent = nullptr);
    static DatabaseManager& instance();

    bool openDatabase(const QString& dbName = "server.db");
    bool setupTables();
    QSqlDatabase getDatabase() const;
    bool validateLogin(const QString& username, const QString& password);
    bool registerUser(const QString& username, const QString& password, const QString& role);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

