/********************************************************************************
** Form generated from reading UI file 'serverapp.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERAPP_H
#define UI_SERVERAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ServerApp
{
public:

    void setupUi(QDialog *ServerApp)
    {
        if (ServerApp->objectName().isEmpty())
            ServerApp->setObjectName("ServerApp");
        ServerApp->resize(400, 300);

        retranslateUi(ServerApp);

        QMetaObject::connectSlotsByName(ServerApp);
    } // setupUi

    void retranslateUi(QDialog *ServerApp)
    {
        ServerApp->setWindowTitle(QCoreApplication::translate("ServerApp", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerApp: public Ui_ServerApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERAPP_H
