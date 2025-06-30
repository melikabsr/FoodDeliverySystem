/********************************************************************************
** Form generated from reading UI file 'food.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOOD_H
#define UI_FOOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Food
{
public:

    void setupUi(QDialog *Food)
    {
        if (Food->objectName().isEmpty())
            Food->setObjectName("Food");
        Food->resize(400, 300);

        retranslateUi(Food);

        QMetaObject::connectSlotsByName(Food);
    } // setupUi

    void retranslateUi(QDialog *Food)
    {
        Food->setWindowTitle(QCoreApplication::translate("Food", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Food: public Ui_Food {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOOD_H
