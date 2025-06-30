/********************************************************************************
** Form generated from reading UI file 'adminmenuwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMENUWIDGET_H
#define UI_ADMINMENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AdminMenuWidget
{
public:

    void setupUi(QDialog *AdminMenuWidget)
    {
        if (AdminMenuWidget->objectName().isEmpty())
            AdminMenuWidget->setObjectName("AdminMenuWidget");
        AdminMenuWidget->resize(400, 300);

        retranslateUi(AdminMenuWidget);

        QMetaObject::connectSlotsByName(AdminMenuWidget);
    } // setupUi

    void retranslateUi(QDialog *AdminMenuWidget)
    {
        AdminMenuWidget->setWindowTitle(QCoreApplication::translate("AdminMenuWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminMenuWidget: public Ui_AdminMenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMENUWIDGET_H
