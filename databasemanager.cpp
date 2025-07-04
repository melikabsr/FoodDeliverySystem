#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent)
{}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::openDatabase(const QString& dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qWarning() << "❌ Failed to open database:" << db.lastError().text();
        return false;
    }

    qDebug() << "✅ Database opened successfully.";
    return true;
}


bool DatabaseManager::setupTables()
{
    QSqlQuery query(getDatabase());
    bool success = true;
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE, "
        "password TEXT, "
        "role TEXT, "
        "restaurant_id INTEGER)"
        );


    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS restaurants ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "address TEXT, "
        "owner_username TEXT)");

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS foods ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "restaurant_id INTEGER, "
        "name TEXT, "
        "description TEXT, "
        "price REAL)");

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS orders ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "customer_username TEXT, "
        "status TEXT, "
        "timestamp TEXT)");

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS order_items ("
        "order_id INTEGER, "
        "food_name TEXT, "
        "quantity INTEGER, "
        "price REAL)");

    if (!success)
        qWarning() << "❌ Error creating tables:" << query.lastError().text();

    return success;
}


bool DatabaseManager::registerUser(const QString& username, const QString& password, const QString& role)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(role);

    if (!query.exec()) {
        qWarning() << "❌ registerUser failed:" << query.lastError().text();
        return false;
    }

    return true;
}
QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}
