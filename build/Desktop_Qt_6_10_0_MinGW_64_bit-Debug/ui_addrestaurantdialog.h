/********************************************************************************
** Form generated from reading UI file 'addrestaurantdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESTAURANTDIALOG_H
#define UI_ADDRESTAURANTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AddRestaurantDialog
{
public:

    void setupUi(QDialog *AddRestaurantDialog)
    {
        if (AddRestaurantDialog->objectName().isEmpty())
            AddRestaurantDialog->setObjectName("AddRestaurantDialog");
        AddRestaurantDialog->resize(400, 300);

        retranslateUi(AddRestaurantDialog);

        QMetaObject::connectSlotsByName(AddRestaurantDialog);
    } // setupUi

    void retranslateUi(QDialog *AddRestaurantDialog)
    {
        AddRestaurantDialog->setWindowTitle(QCoreApplication::translate("AddRestaurantDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddRestaurantDialog: public Ui_AddRestaurantDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESTAURANTDIALOG_H
