#include "OrderStatusEditor.h"
#include <QMessageBox>

OrderStatusEditor::OrderStatusEditor(int orderId, ClientNetwork* network, QWidget* parent)
    : QWidget(parent), orderId(orderId), network(network)
{
    setWindowTitle("✏️ Change Order Status");
    resize(300, 150);

    QVBoxLayout* layout = new QVBoxLayout(this);

    statusCombo = new QComboBox(this);
    statusCombo->addItems({"PENDING", "CONFIRMED", "PREPARING", "READY", "DELIVERED", "CANCELLED"});

    submitBtn = new QPushButton("✅ Update Status", this);

    layout->addWidget(new QLabel("Select new status:"));
    layout->addWidget(statusCombo);
    layout->addWidget(submitBtn);
    setLayout(layout);

    connect(submitBtn, &QPushButton::clicked, this, &OrderStatusEditor::onSubmitClicked);
}

void OrderStatusEditor::onSubmitClicked()
{
    QString status = statusCombo->currentText();
    QString message = QString("UPDATE_ORDER_STATUS|%1|%2").arg(orderId).arg(status);
    network->sendMessage(message);

    QMessageBox::information(this, "✅ Updated", "Order status sent to server.");
    emit statusUpdated(); // سیگنال دلخواه برای تازه‌سازی لیست
    close();
}
