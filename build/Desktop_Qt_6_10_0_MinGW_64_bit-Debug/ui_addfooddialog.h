/********************************************************************************
** Form generated from reading UI file 'addfooddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFOODDIALOG_H
#define UI_ADDFOODDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AddFoodDialog
{
public:

    void setupUi(QDialog *AddFoodDialog)
    {
        if (AddFoodDialog->objectName().isEmpty())
            AddFoodDialog->setObjectName("AddFoodDialog");
        AddFoodDialog->resize(400, 300);

        retranslateUi(AddFoodDialog);

        QMetaObject::connectSlotsByName(AddFoodDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFoodDialog)
    {
        AddFoodDialog->setWindowTitle(QCoreApplication::translate("AddFoodDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFoodDialog: public Ui_AddFoodDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFOODDIALOG_H
