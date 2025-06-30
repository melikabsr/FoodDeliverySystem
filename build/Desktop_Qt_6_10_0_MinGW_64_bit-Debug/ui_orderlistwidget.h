/********************************************************************************
** Form generated from reading UI file 'orderlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERLISTWIDGET_H
#define UI_ORDERLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_orderlistwidget
{
public:

    void setupUi(QDialog *orderlistwidget)
    {
        if (orderlistwidget->objectName().isEmpty())
            orderlistwidget->setObjectName("orderlistwidget");
        orderlistwidget->resize(400, 300);

        retranslateUi(orderlistwidget);

        QMetaObject::connectSlotsByName(orderlistwidget);
    } // setupUi

    void retranslateUi(QDialog *orderlistwidget)
    {
        orderlistwidget->setWindowTitle(QCoreApplication::translate("orderlistwidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class orderlistwidget: public Ui_orderlistwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERLISTWIDGET_H
