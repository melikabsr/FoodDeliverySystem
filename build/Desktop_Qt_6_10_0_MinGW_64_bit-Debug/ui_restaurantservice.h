/********************************************************************************
** Form generated from reading UI file 'restaurantservice.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTSERVICE_H
#define UI_RESTAURANTSERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantService
{
public:

    void setupUi(QDialog *RestaurantService)
    {
        if (RestaurantService->objectName().isEmpty())
            RestaurantService->setObjectName("RestaurantService");
        RestaurantService->resize(400, 300);

        retranslateUi(RestaurantService);

        QMetaObject::connectSlotsByName(RestaurantService);
    } // setupUi

    void retranslateUi(QDialog *RestaurantService)
    {
        RestaurantService->setWindowTitle(QCoreApplication::translate("RestaurantService", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantService: public Ui_RestaurantService {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTSERVICE_H
