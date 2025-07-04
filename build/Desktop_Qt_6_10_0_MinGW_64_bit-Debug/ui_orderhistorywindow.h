/********************************************************************************
** Form generated from reading UI file 'orderhistorywindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERHISTORYWINDOW_H
#define UI_ORDERHISTORYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_orderhistorywindow
{
public:

    void setupUi(QDialog *orderhistorywindow)
    {
        if (orderhistorywindow->objectName().isEmpty())
            orderhistorywindow->setObjectName("orderhistorywindow");
        orderhistorywindow->resize(400, 300);

        retranslateUi(orderhistorywindow);

        QMetaObject::connectSlotsByName(orderhistorywindow);
    } // setupUi

    void retranslateUi(QDialog *orderhistorywindow)
    {
        orderhistorywindow->setWindowTitle(QCoreApplication::translate("orderhistorywindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class orderhistorywindow: public Ui_orderhistorywindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERHISTORYWINDOW_H
