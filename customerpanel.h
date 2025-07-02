
#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class CustomerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerPanel(QWidget *parent = nullptr);

private slots:
    void showOrderHistory();

private:
    QLabel* welcomeLabel;
    QPushButton* viewRestaurantsButton;
    QPushButton* viewCartButton;
    QPushButton* viewOrdersButton;
    QPushButton* logoutButton;
    QPushButton* historyBtn ;
};

#endif // CUSTOMERPANEL_H
