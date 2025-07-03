#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "clientnetwork.h"
#include <QPushButton>
#include <QMap>
#include "ClientNetwork.h"
class MenuWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWindow(ClientNetwork* net, int restaurantId, const QString& restaurantName, QWidget* parent = nullptr);

private slots:
    void onMessageReceived(const QString& msg);
    void onItemDoubleClicked(QListWidgetItem* item);
    void onSubmitOrderClicked();

private:
    ClientNetwork* network;
    int rId;
    QString rName;
    QListWidget* foodList;
    QPushButton* submitButton;

    QMap<QString, int> cart;

};

#endif // MENUWINDOW_H
