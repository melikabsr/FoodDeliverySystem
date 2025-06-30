QT       += core gui
QT       += core gui widgets

CONFIG   += c++17
TEMPLATE = app
TARGET = FoodDelivery_project
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    customer.cpp \
    customerpanel.cpp \
    food.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwidget.cpp \
    restaurant.cpp \
    restaurantlistwidget.cpp \
    restaurantowner.cpp \
    user.cpp \
    userfactory.cpp

HEADERS += \
    admin.h \
    customer.h \
    customerpanel.h \
    enums.h \
    food.h \
    logindialog.h \
    mainwindow.h \
    menuwidget.h \
    restaurant.h \
    restaurantlistwidget.h \
    restaurantowner.h \
    user.h \
    userfactory.h

FORMS += \
    admin.ui \
    customer.ui \
    customerpanel.ui \
    food.ui \
    logindialog.ui \
    mainwindow.ui \
    menuwidget.ui \
    restaurant.ui \
    restaurantlistwidget.ui \
    restaurantowner.ui \
    user.ui \
    userfactory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
