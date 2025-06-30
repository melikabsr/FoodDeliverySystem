QT       += widgets

CONFIG   += c++17
TEMPLATE = app
TARGET = FoodDelivery_project

SOURCES += \
    admin.cpp \
    customer.cpp \
    customerpanel.cpp \
    customerservice.cpp \
    food.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwidget.cpp \
    order.cpp \
    restaurant.cpp \
    restaurantlistwidget.cpp \
    restaurantowner.cpp \
    shoppingcartwidget.cpp \
    user.cpp \
    userfactory.cpp

HEADERS += \
    admin.h \
    customer.h \
    customerpanel.h \
    customerservice.h \
    enums.h \
    food.h \
    logindialog.h \
    mainwindow.h \
    menuwidget.h \
    order.h \
    restaurant.h \
    restaurantlistwidget.h \
    restaurantowner.h \
    shoppingcartwidget.h \
    user.h \
    userfactory.h

FORMS += \
    admin.ui \
    customer.ui \
    customerpanel.ui \
    customerservice.ui \
    food.ui \
    logindialog.ui \
    mainwindow.ui \
    menuwidget.ui \
    order.ui \
    restaurant.ui \
    restaurantlistwidget.ui \
    restaurantowner.ui \
    shoppingcartwidget.ui \
    user.ui \
    userfactory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
