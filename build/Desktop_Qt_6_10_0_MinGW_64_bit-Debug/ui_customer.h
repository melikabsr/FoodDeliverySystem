/********************************************************************************
** Form generated from reading UI file 'customer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMER_H
#define UI_CUSTOMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Customer
{
public:

    void setupUi(QDialog *Customer)
    {
        if (Customer->objectName().isEmpty())
            Customer->setObjectName("Customer");
        Customer->resize(400, 300);

        retranslateUi(Customer);

        QMetaObject::connectSlotsByName(Customer);
    } // setupUi

    void retranslateUi(QDialog *Customer)
    {
        Customer->setWindowTitle(QCoreApplication::translate("Customer", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Customer: public Ui_Customer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMER_H
