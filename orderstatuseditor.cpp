/*

#include "OrderStatusEditor.h"
#include "ClientNetwork.h"
#include <QMessageBox>

OrderStatusEditor::OrderStatusEditor(int id, QWidget* parent)
    : QWidget(parent), orderId(id)
{
    setWindowTitle("✏️ Edit Order Status");
    resize(300, 150);

    statusCombo = new QComboBox(this);
    statusCombo->addItem("PENDING");
    statusCombo->addItem("PREPARING");
    statusCombo->addItem("READY");
    statusCombo->addItem("DELIVERED");
    statusCombo->addItem("CANCELLED");

    submitBtn = new QPushButton("✅ Update Status");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString("🧾 Order #%1").arg(orderId)));
    layout->addWidget(statusCombo);
    layout->addWidget(submitBtn);

    connect(submitBtn, &QPushButton::clicked, this, &OrderStatusEditor::onSubmitClicked);
}

void OrderStatusEditor::onSubmitClicked()
{
    QString selectedStatus = statusCombo->currentText();
    QString message = QString("UPDATE_ORDER_STATUS|%1|%2").arg(orderId).arg(selectedStatus);

    ClientNetwork::instance().sendMessage(message);
    QMessageBox::information(this, "Updated", "Order status updated successfully.");

    emit statusUpdated();
    close();
}
*/




#include "OrderStatusEditor.h"
#include "ClientNetwork.h"
#include <QMessageBox>
#include <QDialog>


OrderStatusEditor::OrderStatusEditor(int orderId, ClientNetwork* network, QWidget* parent)
    : QWidget(parent), orderId(orderId), network(network)
{
    setWindowTitle("✏️ Change Order Status");
    resize(300, 150);

    QVBoxLayout* layout = new QVBoxLayout(this);

    statusCombo = new QComboBox(this);
    statusCombo->addItems({"CONFIRMED", "PREPARING", "READY", "DELIVERED"});

    submitBtn = new QPushButton("Update Status", this);

    layout->addWidget(statusCombo);
    layout->addWidget(submitBtn);

    connect(submitBtn, &QPushButton::clicked, this, &OrderStatusEditor::onSubmitClicked);
}


// OrderStatusEditor::OrderStatusEditor(int orderId, ClientNetwork* network, QWidget* parent)
//     : QDialog(parent), orderId(orderId), network(network)
// {
//     setWindowTitle("✏️ Change Order Status");
//     resize(300, 150);

//     QVBoxLayout* layout = new QVBoxLayout(this);

//     statusCombo = new QComboBox(this);
//     statusCombo->addItems({"CONFIRMED", "PREPARING", "READY", "DELIVERED"});

//     submitBtn = new QPushButton("Update Status", this);

//     layout->addWidget(statusCombo);
//     layout->addWidget(submitBtn);

//     connect(submitBtn, &QPushButton::clicked, this, &OrderStatusEditor::onSubmitClicked);
// }

// void OrderStatusEditor::onSubmitClicked()
// {
//     QString status = statusCombo->currentText();
//     QString message = QString("UPDATE_ORDER_STATUS|%1|%2").arg(orderId).arg(status);
//     network->sendMessage(message);

//     QMessageBox::information(this, "✅ Updated", "Order status sent to server.");
//     accept();
// }
void OrderStatusEditor::onSubmitClicked()
{
    QString status = statusCombo->currentText();
    QString message = QString("UPDATE_ORDER_STATUS|%1|%2").arg(orderId).arg(status);
    network->sendMessage(message);

    QMessageBox::information(this, "✅ Updated", "Order status sent to server.");
    this->close(); // استفاده مطمئن
}
