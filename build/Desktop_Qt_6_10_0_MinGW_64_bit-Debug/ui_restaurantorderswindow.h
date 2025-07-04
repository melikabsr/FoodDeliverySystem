/********************************************************************************
** Form generated from reading UI file 'restaurantorderswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTORDERSWINDOW_H
#define UI_RESTAURANTORDERSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantOrdersWindow
{
public:

    void setupUi(QDialog *RestaurantOrdersWindow)
    {
        if (RestaurantOrdersWindow->objectName().isEmpty())
            RestaurantOrdersWindow->setObjectName("RestaurantOrdersWindow");
        RestaurantOrdersWindow->resize(400, 300);

        retranslateUi(RestaurantOrdersWindow);

        QMetaObject::connectSlotsByName(RestaurantOrdersWindow);
    } // setupUi

    void retranslateUi(QDialog *RestaurantOrdersWindow)
    {
        RestaurantOrdersWindow->setWindowTitle(QCoreApplication::translate("RestaurantOrdersWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantOrdersWindow: public Ui_RestaurantOrdersWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTORDERSWINDOW_H
