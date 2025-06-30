#ifndef RESTAURANTADMINWIDGET_H
#define RESTAURANTADMINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

class RestaurantAdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantAdminWidget(QWidget *parent = nullptr);

private slots:
    void onAddRestaurantClicked();
    void onRemoveSelectedClicked();
    void refreshList();

private:
    QVBoxLayout* layout;
    QLabel* titleLabel;
    QListWidget* listWidget;
    QPushButton* addBtn;
    QPushButton* removeBtn;
};

#endif // RESTAURANTADMINWIDGET_H
