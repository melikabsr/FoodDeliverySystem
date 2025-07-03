/********************************************************************************
** Form generated from reading UI file 'orderswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERSWINDOW_H
#define UI_ORDERSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OrdersWindow
{
public:

    void setupUi(QDialog *OrdersWindow)
    {
        if (OrdersWindow->objectName().isEmpty())
            OrdersWindow->setObjectName("OrdersWindow");
        OrdersWindow->resize(400, 300);

        retranslateUi(OrdersWindow);

        QMetaObject::connectSlotsByName(OrdersWindow);
    } // setupUi

    void retranslateUi(QDialog *OrdersWindow)
    {
        OrdersWindow->setWindowTitle(QCoreApplication::translate("OrdersWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrdersWindow: public Ui_OrdersWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERSWINDOW_H
