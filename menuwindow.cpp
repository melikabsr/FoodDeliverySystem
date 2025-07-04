
#include "MenuWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "CustomerService.h"
#include <QCloseEvent>

MenuWindow::MenuWindow(ClientNetwork* net, int restaurantId, const QString& restaurantName, QWidget* parent)
    : QWidget(parent), network(net), rId(restaurantId), rName(restaurantName)
{
    setWindowTitle(QString("📋 Menu - %1").arg(restaurantName));
    resize(450, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);
    foodList = new QListWidget(this);
    submitButton = new QPushButton("📤 ثبت سفارش");

    layout->addWidget(new QLabel(QString("🍽️ Menu for %1").arg(restaurantName)));
    layout->addWidget(foodList);
    layout->addWidget(submitButton);

    connect(foodList, &QListWidget::itemDoubleClicked, this, &MenuWindow::onItemDoubleClicked);
    connect(submitButton, &QPushButton::clicked, this, &MenuWindow::onSubmitOrderClicked);
    connect(network, &ClientNetwork::messageReceived, this, &MenuWindow::onMessageReceived);

    // درخواست منو از سرور
    network->sendMessage(QString("GET_MENU|%1").arg(rId));
}

void MenuWindow::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("MENU|")) return;

    QStringList rows = msg.section("|", 1).split("|");  // ✅ اصلاح شده
    foodList->clear();

    for (const QString& row : rows) {
        QStringList cols = row.split("~");  // ✅ چون در سرور با ~ جدا شده
        if (cols.size() < 4) continue;

        QString id = cols[0];
        QString name = cols[1];
        QString desc = cols[2];
        QString price = cols[3];

        QString line = QString("🍛 %1 | %2 | 💵 %3 تومان").arg(name, desc, price);
        QListWidgetItem* item = new QListWidgetItem(line);
        item->setData(Qt::UserRole, name); // برای اضافه‌کردن به cart
        foodList->addItem(item);
    }
}

void MenuWindow::onItemDoubleClicked(QListWidgetItem* item)
{
    QString name = item->data(Qt::UserRole).toString();
    cart[name] += 1;
    QMessageBox::information(this, "Added", name + " added to cart.");
}

void MenuWindow::onSubmitOrderClicked()
{
    if (cart.isEmpty()) {
        QMessageBox::warning(this, "Cart Empty", "هیچ آیتمی انتخاب نشده.");
        return;
    }

    QString username = CustomerService::instance().getCurrentUsername();  // ✅ دریافت خودکار

    QStringList items;
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        items << QString("%1:%2").arg(it.key()).arg(it.value());
    }

    QString msg = QString("ADD_ORDER|%1|%2|%3").arg(username).arg(rId).arg(items.join(","));
    network->sendMessage(msg);
    QMessageBox::information(this, "✅ Done", "سفارش ثبت شد.");

    cart.clear();
}



void MenuWindow::closeEvent(QCloseEvent* event)
{
    disconnect(network, &ClientNetwork::messageReceived, this, nullptr);
    QWidget::closeEvent(event);
}
