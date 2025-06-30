#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>

class UserListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserListWidget(QWidget *parent = nullptr);

private:
    QListWidget* listWidget;
};


#endif
