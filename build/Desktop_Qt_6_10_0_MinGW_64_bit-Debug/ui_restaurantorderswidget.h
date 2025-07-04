/********************************************************************************
** Form generated from reading UI file 'restaurantorderswidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTORDERSWIDGET_H
#define UI_RESTAURANTORDERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantOrdersWidget
{
public:

    void setupUi(QDialog *RestaurantOrdersWidget)
    {
        if (RestaurantOrdersWidget->objectName().isEmpty())
            RestaurantOrdersWidget->setObjectName("RestaurantOrdersWidget");
        RestaurantOrdersWidget->resize(400, 300);

        retranslateUi(RestaurantOrdersWidget);

        QMetaObject::connectSlotsByName(RestaurantOrdersWidget);
    } // setupUi

    void retranslateUi(QDialog *RestaurantOrdersWidget)
    {
        RestaurantOrdersWidget->setWindowTitle(QCoreApplication::translate("RestaurantOrdersWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantOrdersWidget: public Ui_RestaurantOrdersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTORDERSWIDGET_H
