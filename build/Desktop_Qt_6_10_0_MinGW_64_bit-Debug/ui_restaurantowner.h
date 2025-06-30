/********************************************************************************
** Form generated from reading UI file 'restaurantowner.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTOWNER_H
#define UI_RESTAURANTOWNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantOwner
{
public:

    void setupUi(QDialog *RestaurantOwner)
    {
        if (RestaurantOwner->objectName().isEmpty())
            RestaurantOwner->setObjectName("RestaurantOwner");
        RestaurantOwner->resize(400, 300);

        retranslateUi(RestaurantOwner);

        QMetaObject::connectSlotsByName(RestaurantOwner);
    } // setupUi

    void retranslateUi(QDialog *RestaurantOwner)
    {
        RestaurantOwner->setWindowTitle(QCoreApplication::translate("RestaurantOwner", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantOwner: public Ui_RestaurantOwner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTOWNER_H
