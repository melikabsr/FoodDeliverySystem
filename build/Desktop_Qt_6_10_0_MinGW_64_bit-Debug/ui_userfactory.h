/********************************************************************************
** Form generated from reading UI file 'userfactory.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFACTORY_H
#define UI_USERFACTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_UserFactory
{
public:

    void setupUi(QDialog *UserFactory)
    {
        if (UserFactory->objectName().isEmpty())
            UserFactory->setObjectName("UserFactory");
        UserFactory->resize(400, 300);

        retranslateUi(UserFactory);

        QMetaObject::connectSlotsByName(UserFactory);
    } // setupUi

    void retranslateUi(QDialog *UserFactory)
    {
        UserFactory->setWindowTitle(QCoreApplication::translate("UserFactory", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserFactory: public Ui_UserFactory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFACTORY_H
