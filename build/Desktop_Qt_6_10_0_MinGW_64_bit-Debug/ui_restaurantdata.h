/********************************************************************************
** Form generated from reading UI file 'restaurantdata.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTDATA_H
#define UI_RESTAURANTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantData
{
public:

    void setupUi(QDialog *RestaurantData)
    {
        if (RestaurantData->objectName().isEmpty())
            RestaurantData->setObjectName("RestaurantData");
        RestaurantData->resize(400, 300);

        retranslateUi(RestaurantData);

        QMetaObject::connectSlotsByName(RestaurantData);
    } // setupUi

    void retranslateUi(QDialog *RestaurantData)
    {
        RestaurantData->setWindowTitle(QCoreApplication::translate("RestaurantData", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantData: public Ui_RestaurantData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTDATA_H
