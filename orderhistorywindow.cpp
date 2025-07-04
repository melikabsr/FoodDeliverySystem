
#include "OrderHistoryWindow.h"
#include <QVBoxLayout>
#include <QLabel>

    OrderHistoryWindow::OrderHistoryWindow(ClientNetwork* network, const QString& username, QWidget* parent)
    : QWidget(parent), network(network), user(username)
{
    setWindowTitle("📜 Order History");
    resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("📦 سفارش‌های قبلی شما:"));

    list = new QListWidget(this);
    layout->addWidget(list);

    connect(network, &ClientNetwork::messageReceived, this, &OrderHistoryWindow::onMessageReceived);

    // درخواست تاریخچه سفارش‌ها از سرور
    network->sendMessage(QString("GET_ORDERS|%1").arg(user));
}

void OrderHistoryWindow::onMessageReceived(const QString& msg)
{
    if (!msg.startsWith("ORDERS|"))
        return;

    list->clear();

    QString data = msg.section("|", 1);
    QStringList rows = data.split(";");

    for (const QString& row : rows) {
        if (!row.trimmed().isEmpty()) {
            list->addItem(new QListWidgetItem(row));
        }
    }
}
