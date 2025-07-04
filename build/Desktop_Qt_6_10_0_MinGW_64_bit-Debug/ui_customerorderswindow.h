/********************************************************************************
** Form generated from reading UI file 'customerorderswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERORDERSWINDOW_H
#define UI_CUSTOMERORDERSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CustomerOrdersWindow
{
public:

    void setupUi(QDialog *CustomerOrdersWindow)
    {
        if (CustomerOrdersWindow->objectName().isEmpty())
            CustomerOrdersWindow->setObjectName("CustomerOrdersWindow");
        CustomerOrdersWindow->resize(400, 300);

        retranslateUi(CustomerOrdersWindow);

        QMetaObject::connectSlotsByName(CustomerOrdersWindow);
    } // setupUi

    void retranslateUi(QDialog *CustomerOrdersWindow)
    {
        CustomerOrdersWindow->setWindowTitle(QCoreApplication::translate("CustomerOrdersWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomerOrdersWindow: public Ui_CustomerOrdersWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERORDERSWINDOW_H
