// #include <QCoreApplication>
// #include "ServerApp.h"
// #include "DatabaseManager.h"

// int main(int argc, char *argv[])
// {
//     QCoreApplication app(argc, argv);
//     DatabaseManager::instance().openDatabase();
//     DatabaseManager::instance().setupTables();

//     ServerApp server;
//     server.startServer(1234);
//     return app.exec();
// }

#include <QCoreApplication>
#include "ServerApp.h"
#include "DatabaseManager.h"
#include <QDebug>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // مسیر دیتابیس
    QString databasePath = QCoreApplication::applicationDirPath() + "/food.db";
    qDebug() << "📁 Trying to open DB at: " << databasePath;

    // اتصال به پایگاه‌داده
    if (!DatabaseManager::instance().openDatabase(databasePath)) {
        qCritical() << "❌ Failed to open database.";
        return -1;
    }

    // ایجاد جدول‌ها (در صورت نیاز)
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, role TEXT)");
    q.exec("CREATE TABLE IF NOT EXISTS restaurants (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, owner_username TEXT)");
    q.exec("CREATE TABLE IF NOT EXISTS foods (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, description TEXT, price REAL, restaurant_name TEXT)");
    q.exec("CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY, customer_username TEXT, status TEXT, timestamp TEXT)");
    q.exec("CREATE TABLE IF NOT EXISTS order_items (order_id INTEGER, food_name TEXT, quantity INTEGER)");

    // راه‌اندازی سرور
    ServerApp server;
    if (!server.startServer(1234)) {
        qCritical() << "❌ Failed to start server on port 1234.";
        return -3;
    }

    qDebug() << "✅ Server started successfully on port 1234.";
    return app.exec();
}
