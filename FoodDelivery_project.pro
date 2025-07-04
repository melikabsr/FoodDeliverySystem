QT       += widgets
QT       += core
CONFIG   += c++17
 QT += sql
TEMPLATE = app
TARGET = FoodDelivery_project
 QT += network
SOURCES += \
    addfooddialog.cpp \
    addrestaurantdialog.cpp \
    admin.cpp \
    adminmenuwidget.cpp \
    adminpanel.cpp \
    clientdatabasemanager.cpp \
    clientnetwork.cpp \
    customer.cpp \
    customerorderswindow.cpp \
    customerpanel.cpp \
    customerservice.cpp \
    food.cpp \
    logindialog.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwidget.cpp \
    menuwindow.cpp \
    order.cpp \
    orderhistorywidget.cpp \
    orderhistorywindow.cpp \
    orderlistwidget.cpp \
    ordermanager.cpp \
    orderstatuseditor.cpp \
    orderswindow.cpp \
    restaurant.cpp \
    restaurantadminwidget.cpp \
    restaurantlistwidget.cpp \
    restaurantlistwindow.cpp \
    restaurantorderswidget.cpp \
    restaurantorderswindow.cpp \
    restaurantowner.cpp \
    restaurantownerpanel.cpp \
    restaurantservice.cpp \
    shoppingcartwidget.cpp \
    user.cpp \
    userfactory.cpp \
    userlistwidget.cpp

HEADERS += \
    DebugTestWindow.h \
    addfooddialog.h \
    addrestaurantdialog.h \
    admin.h \
    adminmenuwidget.h \
    adminpanel.h \
    clientdatabasemanager.h \
    clientnetwork.h \
    customer.h \
    customerorderswindow.h \
    customerpanel.h \
    customerservice.h \
    enums.h \
    food.h \
    logindialog.h \
    loginwindow.h \
    mainwindow.h \
    menuwidget.h \
    menuwindow.h \
    order.h \
    orderhistorywidget.h \
    orderhistorywindow.h \
    orderlistwidget.h \
    ordermanager.h \
    orderstatuseditor.h \
    orderswindow.h \
    restaurant.h \
    restaurantadminwidget.h \
    restaurantlistwidget.h \
    restaurantlistwindow.h \
    restaurantorderswidget.h \
    restaurantorderswindow.h \
    restaurantowner.h \
    restaurantownerpanel.h \
    restaurantservice.h \
    shoppingcartwidget.h \
    user.h \
    userfactory.h \
    userlistwidget.h

FORMS += \
    addfooddialog.ui \
    addrestaurantdialog.ui \
    admin.ui \
    adminmenuwidget.ui \
    adminpanel.ui \
    clientdatabasemanager.ui \
    clientnetwork.ui \
    customer.ui \
    customerorderswindow.ui \
    customerpanel.ui \
    customerservice.ui \
    food.ui \
    logindialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    menuwidget.ui \
    menuwindow.ui \
    order.ui \
    orderhistorywidget.ui \
    orderhistorywindow.ui \
    orderlistwidget.ui \
    ordermanager.ui \
    orderstatuseditor.ui \
    orderswindow.ui \
    restaurant.ui \
    restaurantadminwidget.ui \
    restaurantlistwidget.ui \
    restaurantlistwindow.ui \
    restaurantorderswidget.ui \
    restaurantorderswindow.ui \
    restaurantowner.ui \
    restaurantownerpanel.ui \
    restaurantservice.ui \
    shoppingcartwidget.ui \
    user.ui \
    userfactory.ui \
    userlistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
