#ifndef ORDERSTATUSEDITOR_H
#define ORDERSTATUSEDITOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "ClientNetwork.h"

class OrderStatusEditor : public QWidget
{
    Q_OBJECT

public:
    explicit OrderStatusEditor(int orderId, ClientNetwork* network, QWidget* parent = nullptr);

signals:
    void statusUpdated();

private slots:
    void onSubmitClicked();

private:
    ClientNetwork* network;
    int orderId;
    QComboBox* statusCombo;
    QPushButton* submitBtn;
};

#endif // ORDERSTATUSEDITOR_H
