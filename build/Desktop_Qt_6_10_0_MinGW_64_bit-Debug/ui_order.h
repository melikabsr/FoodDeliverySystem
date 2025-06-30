/********************************************************************************
** Form generated from reading UI file 'order.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDER_H
#define UI_ORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Order
{
public:

    void setupUi(QDialog *Order)
    {
        if (Order->objectName().isEmpty())
            Order->setObjectName("Order");
        Order->resize(400, 300);

        retranslateUi(Order);

        QMetaObject::connectSlotsByName(Order);
    } // setupUi

    void retranslateUi(QDialog *Order)
    {
        Order->setWindowTitle(QCoreApplication::translate("Order", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Order: public Ui_Order {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDER_H
