#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);

private slots:
    void onViewUsersClicked();
    void onViewOrdersClicked();
    void onExitClicked();

private:
    QLabel* titleLabel;
    QPushButton* viewUsersBtn;
    QPushButton* viewOrdersBtn;
    QPushButton* exitBtn;
    QVBoxLayout* layout;
};

#endif // ADMINPANEL_H
