#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QObject>
#include <QMap>

class UserDatabase : public QObject
{
    Q_OBJECT

public:
    static UserDatabase& instance();

    bool validateLogin(const QString& username, const QString& password) const;
    void addUser(const QString& username, const QString& password, const QString& role);
    QString getRole(const QString& username) const;

private:
    explicit UserDatabase(QObject* parent = nullptr);
    QMap<QString, QPair<QString, QString>> users; // key = username → (password, role)
};

#endif // USERDATABASE_H
