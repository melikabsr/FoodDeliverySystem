/********************************************************************************
** Form generated from reading UI file 'adminpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AdminPanel
{
public:

    void setupUi(QDialog *AdminPanel)
    {
        if (AdminPanel->objectName().isEmpty())
            AdminPanel->setObjectName("AdminPanel");
        AdminPanel->resize(400, 300);

        retranslateUi(AdminPanel);

        QMetaObject::connectSlotsByName(AdminPanel);
    } // setupUi

    void retranslateUi(QDialog *AdminPanel)
    {
        AdminPanel->setWindowTitle(QCoreApplication::translate("AdminPanel", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPanel: public Ui_AdminPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
