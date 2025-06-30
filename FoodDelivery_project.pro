QT       += widgets
QT       += core
CONFIG   += c++17
TEMPLATE = app
TARGET = FoodDelivery_project

SOURCES += \
    addfooddialog.cpp \
    addrestaurantdialog.cpp \
    admin.cpp \
    adminpanel.cpp \
    customer.cpp \
    customerpanel.cpp \
    customerservice.cpp \
    food.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwidget.cpp \
    order.cpp \
    orderhistorywidget.cpp \
    orderlistwidget.cpp \
    ordermanager.cpp \
    restaurant.cpp \
    restaurantadminwidget.cpp \
    restaurantlistwidget.cpp \
    restaurantowner.cpp \
    restaurantownerpanel.cpp \
    shoppingcartwidget.cpp \
    user.cpp \
    userfactory.cpp \
    userlistwidget.cpp

HEADERS += \
    addfooddialog.h \
    addrestaurantdialog.h \
    admin.h \
    adminpanel.h \
    customer.h \
    customerpanel.h \
    customerservice.h \
    enums.h \
    food.h \
    logindialog.h \
    mainwindow.h \
    menuwidget.h \
    order.h \
    orderhistorywidget.h \
    orderlistwidget.h \
    ordermanager.h \
    restaurant.h \
    restaurantadminwidget.h \
    restaurantlistwidget.h \
    restaurantowner.h \
    restaurantownerpanel.h \
    shoppingcartwidget.h \
    user.h \
    userfactory.h \
    userlistwidget.h

FORMS += \
    addfooddialog.ui \
    addrestaurantdialog.ui \
    admin.ui \
    adminpanel.ui \
    customer.ui \
    customerpanel.ui \
    customerservice.ui \
    food.ui \
    logindialog.ui \
    mainwindow.ui \
    menuwidget.ui \
    order.ui \
    orderhistorywidget.ui \
    orderlistwidget.ui \
    ordermanager.ui \
    restaurant.ui \
    restaurantadminwidget.ui \
    restaurantlistwidget.ui \
    restaurantowner.ui \
    restaurantownerpanel.ui \
    shoppingcartwidget.ui \
    user.ui \
    userfactory.ui \
    userlistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
