

#include "menuwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>
#include <QMessageBox>

MenuWindow::MenuWindow(ClientNetwork* net, int restaurantId, const QString& restaurantName, QWidget* parent)
    : QWidget(parent), network(net), rId(restaurantId), rName(restaurantName)
{
    setWindowTitle(QString("📋 Menu - %1").arg(restaurantName));
    resize(400, 500);

    foodList = new QListWidget(this);
    submitButton = new QPushButton("📤 ثبت سفارش", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString("🍽️ Menu for %1").arg(restaurantName)));
    layout->addWidget(foodList);
    layout->addWidget(submitButton);

    connect(foodList, &QListWidget::itemDoubleClicked, this, &MenuWindow::onItemDoubleClicked);
    connect(submitButton, &QPushButton::clicked, this, &MenuWindow::onSubmitOrderClicked);
    connect(network, &ClientNetwork::messageReceived, this, &MenuWindow::onMessageReceived);

    network->sendMessage(QString("GET_MENU|%1").arg(rId));
}

void MenuWindow::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("MENU|")) return;

    QString data = msg.section("|", 1);
    QStringList rows = data.split(";");

    foodList->clear();
    for (const QString& row : rows) {
        QStringList cols = row.split(",");
        if (cols.size() < 3) continue;

        QString name = cols[0];
        QString desc = cols[1];
        QString price = cols[2];

        QString line = QString("%1|%2|%3").arg(name, desc, price);
        foodList->addItem(line);
    }
}

void MenuWindow::onItemDoubleClicked(QListWidgetItem* item)
{
    QStringList parts = item->text().split("|");
    if (parts.size() < 1) return;

    QString foodName = parts[0];
    cart[foodName] += 1;

    QMessageBox::information(this, "➕ Added", foodName + " added to cart.");
}

void MenuWindow::onSubmitOrderClicked()
{
    if (cart.isEmpty()) {
        QMessageBox::warning(this, "Cart Empty", "سبد خرید خالی است.");
        return;
    }

    // فرض: username در سمت کلاینت مشخصه، اینجا تستی
    QString username = "ali";

    QStringList orderItems;
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        orderItems << QString("%1:%2").arg(it.key()).arg(it.value());
    }

    QString message = QString("ADD_ORDER|%1|%2|%3").arg(username).arg(rId).arg(orderItems.join(","));
    network->sendMessage(message);

    QMessageBox::information(this, "✅ Success", "سفارش ارسال شد!");
    cart.clear();
}





