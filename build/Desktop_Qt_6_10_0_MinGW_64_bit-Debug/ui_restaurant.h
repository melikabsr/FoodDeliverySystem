/********************************************************************************
** Form generated from reading UI file 'restaurant.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANT_H
#define UI_RESTAURANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Restaurant
{
public:

    void setupUi(QDialog *Restaurant)
    {
        if (Restaurant->objectName().isEmpty())
            Restaurant->setObjectName("Restaurant");
        Restaurant->resize(400, 300);

        retranslateUi(Restaurant);

        QMetaObject::connectSlotsByName(Restaurant);
    } // setupUi

    void retranslateUi(QDialog *Restaurant)
    {
        Restaurant->setWindowTitle(QCoreApplication::translate("Restaurant", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Restaurant: public Ui_Restaurant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANT_H
