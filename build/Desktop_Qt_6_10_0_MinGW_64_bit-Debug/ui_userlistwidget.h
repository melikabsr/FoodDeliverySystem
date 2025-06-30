/********************************************************************************
** Form generated from reading UI file 'userlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLISTWIDGET_H
#define UI_USERLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_userlistwidget
{
public:

    void setupUi(QDialog *userlistwidget)
    {
        if (userlistwidget->objectName().isEmpty())
            userlistwidget->setObjectName("userlistwidget");
        userlistwidget->resize(400, 300);

        retranslateUi(userlistwidget);

        QMetaObject::connectSlotsByName(userlistwidget);
    } // setupUi

    void retranslateUi(QDialog *userlistwidget)
    {
        userlistwidget->setWindowTitle(QCoreApplication::translate("userlistwidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userlistwidget: public Ui_userlistwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLISTWIDGET_H
