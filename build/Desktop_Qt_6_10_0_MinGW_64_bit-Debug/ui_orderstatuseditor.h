/********************************************************************************
** Form generated from reading UI file 'orderstatuseditor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERSTATUSEDITOR_H
#define UI_ORDERSTATUSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OrderStatusEditor
{
public:

    void setupUi(QDialog *OrderStatusEditor)
    {
        if (OrderStatusEditor->objectName().isEmpty())
            OrderStatusEditor->setObjectName("OrderStatusEditor");
        OrderStatusEditor->resize(400, 300);

        retranslateUi(OrderStatusEditor);

        QMetaObject::connectSlotsByName(OrderStatusEditor);
    } // setupUi

    void retranslateUi(QDialog *OrderStatusEditor)
    {
        OrderStatusEditor->setWindowTitle(QCoreApplication::translate("OrderStatusEditor", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderStatusEditor: public Ui_OrderStatusEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERSTATUSEDITOR_H
