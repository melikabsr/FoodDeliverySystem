QT       += core gui
 QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clienthandler.cpp \
    dialog.cpp \
    food.cpp \
    main.cpp \
    mainwindow.cpp \
    ordermanager.cpp \
    restaurant.cpp \
    restaurantdata.cpp \
    serverapp.cpp \
    serverorder.cpp \
    userdatabase.cpp

HEADERS += \
    clienthandler.h \
    dialog.h \
    food.h \
    mainwindow.h \
    ordermanager.h \
    restaurant.h \
    restaurantdata.h \
    serverapp.h \
    serverorder.h \
    userdatabase.h

FORMS += \
    clienthandler.ui \
    dialog.ui \
    food.ui \
    mainwindow.ui \
    ordermanager.ui \
    restaurant.ui \
    restaurantdata.ui \
    serverapp.ui \
    serverorder.ui \
    userdatabase.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
