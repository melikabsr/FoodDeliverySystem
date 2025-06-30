/********************************************************************************
** Form generated from reading UI file 'shoppingcartwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOPPINGCARTWIDGET_H
#define UI_SHOPPINGCARTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ShoppingCartWidget
{
public:

    void setupUi(QDialog *ShoppingCartWidget)
    {
        if (ShoppingCartWidget->objectName().isEmpty())
            ShoppingCartWidget->setObjectName("ShoppingCartWidget");
        ShoppingCartWidget->resize(400, 300);

        retranslateUi(ShoppingCartWidget);

        QMetaObject::connectSlotsByName(ShoppingCartWidget);
    } // setupUi

    void retranslateUi(QDialog *ShoppingCartWidget)
    {
        ShoppingCartWidget->setWindowTitle(QCoreApplication::translate("ShoppingCartWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShoppingCartWidget: public Ui_ShoppingCartWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOPPINGCARTWIDGET_H
