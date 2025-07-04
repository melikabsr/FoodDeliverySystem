/********************************************************************************
** Form generated from reading UI file 'clientnetwork.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTNETWORK_H
#define UI_CLIENTNETWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_clientnetwork
{
public:

    void setupUi(QDialog *clientnetwork)
    {
        if (clientnetwork->objectName().isEmpty())
            clientnetwork->setObjectName("clientnetwork");
        clientnetwork->resize(400, 300);

        retranslateUi(clientnetwork);

        QMetaObject::connectSlotsByName(clientnetwork);
    } // setupUi

    void retranslateUi(QDialog *clientnetwork)
    {
        clientnetwork->setWindowTitle(QCoreApplication::translate("clientnetwork", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clientnetwork: public Ui_clientnetwork {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTNETWORK_H
