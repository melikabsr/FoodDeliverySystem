/********************************************************************************
** Form generated from reading UI file 'restaurantlistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTLISTWINDOW_H
#define UI_RESTAURANTLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_restaurantlistwindow
{
public:

    void setupUi(QDialog *restaurantlistwindow)
    {
        if (restaurantlistwindow->objectName().isEmpty())
            restaurantlistwindow->setObjectName("restaurantlistwindow");
        restaurantlistwindow->resize(400, 300);

        retranslateUi(restaurantlistwindow);

        QMetaObject::connectSlotsByName(restaurantlistwindow);
    } // setupUi

    void retranslateUi(QDialog *restaurantlistwindow)
    {
        restaurantlistwindow->setWindowTitle(QCoreApplication::translate("restaurantlistwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class restaurantlistwindow: public Ui_restaurantlistwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTLISTWINDOW_H
