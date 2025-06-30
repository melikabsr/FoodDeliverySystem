/********************************************************************************
** Form generated from reading UI file 'restaurantlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTLISTWIDGET_H
#define UI_RESTAURANTLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantListWidget
{
public:

    void setupUi(QDialog *RestaurantListWidget)
    {
        if (RestaurantListWidget->objectName().isEmpty())
            RestaurantListWidget->setObjectName("RestaurantListWidget");
        RestaurantListWidget->resize(400, 300);

        retranslateUi(RestaurantListWidget);

        QMetaObject::connectSlotsByName(RestaurantListWidget);
    } // setupUi

    void retranslateUi(QDialog *RestaurantListWidget)
    {
        RestaurantListWidget->setWindowTitle(QCoreApplication::translate("RestaurantListWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantListWidget: public Ui_RestaurantListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTLISTWIDGET_H
