#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class CustomerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerPanel(QWidget *parent = nullptr);

private:
    QLabel* welcomeLabel;
    QPushButton* viewRestaurantsButton;
    QPushButton* viewCartButton;
    QPushButton* logoutButton;
};

#endif // CUSTOMERPANEL_H
