/********************************************************************************
** Form generated from reading UI file 'orderhistorywidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERHISTORYWIDGET_H
#define UI_ORDERHISTORYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OrderHistoryWidget
{
public:

    void setupUi(QDialog *OrderHistoryWidget)
    {
        if (OrderHistoryWidget->objectName().isEmpty())
            OrderHistoryWidget->setObjectName("OrderHistoryWidget");
        OrderHistoryWidget->resize(400, 300);

        retranslateUi(OrderHistoryWidget);

        QMetaObject::connectSlotsByName(OrderHistoryWidget);
    } // setupUi

    void retranslateUi(QDialog *OrderHistoryWidget)
    {
        OrderHistoryWidget->setWindowTitle(QCoreApplication::translate("OrderHistoryWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderHistoryWidget: public Ui_OrderHistoryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERHISTORYWIDGET_H
