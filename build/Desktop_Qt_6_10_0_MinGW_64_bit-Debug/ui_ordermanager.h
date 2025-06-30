/********************************************************************************
** Form generated from reading UI file 'ordermanager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGER_H
#define UI_ORDERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OrderManager
{
public:

    void setupUi(QDialog *OrderManager)
    {
        if (OrderManager->objectName().isEmpty())
            OrderManager->setObjectName("OrderManager");
        OrderManager->resize(400, 300);

        retranslateUi(OrderManager);

        QMetaObject::connectSlotsByName(OrderManager);
    } // setupUi

    void retranslateUi(QDialog *OrderManager)
    {
        OrderManager->setWindowTitle(QCoreApplication::translate("OrderManager", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManager: public Ui_OrderManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGER_H
