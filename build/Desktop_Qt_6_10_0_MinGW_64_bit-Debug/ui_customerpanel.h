/********************************************************************************
** Form generated from reading UI file 'customerpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERPANEL_H
#define UI_CUSTOMERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CustomerPanel
{
public:

    void setupUi(QDialog *CustomerPanel)
    {
        if (CustomerPanel->objectName().isEmpty())
            CustomerPanel->setObjectName("CustomerPanel");
        CustomerPanel->resize(400, 300);

        retranslateUi(CustomerPanel);

        QMetaObject::connectSlotsByName(CustomerPanel);
    } // setupUi

    void retranslateUi(QDialog *CustomerPanel)
    {
        CustomerPanel->setWindowTitle(QCoreApplication::translate("CustomerPanel", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomerPanel: public Ui_CustomerPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERPANEL_H
