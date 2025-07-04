#include "UserRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

bool UserRepository::addUser(const QString& username, const QString& password, const QString& role, int restaurantId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, role, restaurant_id) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(role);
    query.addBindValue(restaurantId);
    return query.exec();
}

bool UserRepository::userExists(const QString& username) const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next())
        return query.value(0).toInt() > 0;
    return false;
}

bool UserRepository::validateLogin(const QString& username, const QString& password) const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "❌ SQL Error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "🔍 Login check for" << username << ":" << (count > 0 ? "✅ OK" : "❌ Failed");
        return count > 0;
    }

    return false;
}

std::optional<UserData> UserRepository::getUser(const QString& username, const QString& role) const
{
    QString roleUpper = role.trimmed().toUpper(); // حروف بزرگ کن برای مقایسه بدون حساسیت

    QSqlQuery query;
    query.prepare("SELECT username, password, role, restaurant_id "
                  "FROM users WHERE username = ? AND UPPER(role) = ?");
    query.addBindValue(username);
    query.addBindValue(roleUpper);

    if (query.exec() && query.next()) {
        return UserData {
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt()
        };
    }

    return std::nullopt;
}

bool UserRepository::removeUser(const QString& username)
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username = ?");
    query.addBindValue(username);
    return query.exec();
}
