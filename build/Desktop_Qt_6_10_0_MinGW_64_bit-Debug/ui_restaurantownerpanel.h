/********************************************************************************
** Form generated from reading UI file 'restaurantownerpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTOWNERPANEL_H
#define UI_RESTAURANTOWNERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RestaurantOwnerPanel
{
public:

    void setupUi(QDialog *RestaurantOwnerPanel)
    {
        if (RestaurantOwnerPanel->objectName().isEmpty())
            RestaurantOwnerPanel->setObjectName("RestaurantOwnerPanel");
        RestaurantOwnerPanel->resize(400, 300);

        retranslateUi(RestaurantOwnerPanel);

        QMetaObject::connectSlotsByName(RestaurantOwnerPanel);
    } // setupUi

    void retranslateUi(QDialog *RestaurantOwnerPanel)
    {
        RestaurantOwnerPanel->setWindowTitle(QCoreApplication::translate("RestaurantOwnerPanel", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantOwnerPanel: public Ui_RestaurantOwnerPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTOWNERPANEL_H
