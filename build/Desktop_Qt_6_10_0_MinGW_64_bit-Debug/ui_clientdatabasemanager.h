/********************************************************************************
** Form generated from reading UI file 'clientdatabasemanager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTDATABASEMANAGER_H
#define UI_CLIENTDATABASEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ClientDatabaseManager
{
public:

    void setupUi(QDialog *ClientDatabaseManager)
    {
        if (ClientDatabaseManager->objectName().isEmpty())
            ClientDatabaseManager->setObjectName("ClientDatabaseManager");
        ClientDatabaseManager->resize(400, 300);

        retranslateUi(ClientDatabaseManager);

        QMetaObject::connectSlotsByName(ClientDatabaseManager);
    } // setupUi

    void retranslateUi(QDialog *ClientDatabaseManager)
    {
        ClientDatabaseManager->setWindowTitle(QCoreApplication::translate("ClientDatabaseManager", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientDatabaseManager: public Ui_ClientDatabaseManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTDATABASEMANAGER_H
