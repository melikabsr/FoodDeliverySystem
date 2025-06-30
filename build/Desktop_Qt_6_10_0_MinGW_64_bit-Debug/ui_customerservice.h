/********************************************************************************
** Form generated from reading UI file 'customerservice.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERSERVICE_H
#define UI_CUSTOMERSERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CustomerService
{
public:

    void setupUi(QDialog *CustomerService)
    {
        if (CustomerService->objectName().isEmpty())
            CustomerService->setObjectName("CustomerService");
        CustomerService->resize(400, 300);

        retranslateUi(CustomerService);

        QMetaObject::connectSlotsByName(CustomerService);
    } // setupUi

    void retranslateUi(QDialog *CustomerService)
    {
        CustomerService->setWindowTitle(QCoreApplication::translate("CustomerService", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomerService: public Ui_CustomerService {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERSERVICE_H
