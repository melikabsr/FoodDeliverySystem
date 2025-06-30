/********************************************************************************
** Form generated from reading UI file 'restaurantadminwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTADMINWIDGET_H
#define UI_RESTAURANTADMINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantAdminWidget
{
public:

    void setupUi(QDialog *RestaurantAdminWidget)
    {
        if (RestaurantAdminWidget->objectName().isEmpty())
            RestaurantAdminWidget->setObjectName("RestaurantAdminWidget");
        RestaurantAdminWidget->resize(400, 300);

        retranslateUi(RestaurantAdminWidget);

        QMetaObject::connectSlotsByName(RestaurantAdminWidget);
    } // setupUi

    void retranslateUi(QDialog *RestaurantAdminWidget)
    {
        RestaurantAdminWidget->setWindowTitle(QCoreApplication::translate("RestaurantAdminWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantAdminWidget: public Ui_RestaurantAdminWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTADMINWIDGET_H
