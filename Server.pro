QT       += core gui
 QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
 QT += sql
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clienthandler.cpp \
    databasemanager.cpp \
    food.cpp \
    foodrepository.cpp \
    main.cpp \
    ordermanager.cpp \
    orderpersistence.cpp \
    restaurant.cpp \
    restaurantdata.cpp \
    restaurantrepository.cpp \
    serverapp.cpp \
    serverorder.cpp \
    userrepository.cpp

HEADERS += \
    clienthandler.h \
    databasemanager.h \
    food.h \
    foodrepository.h \
    ordermanager.h \
    orderpersistence.h \
    restaurant.h \
    restaurantdata.h \
    restaurantrepository.h \
    serverapp.h \
    serverorder.h \
    userrepository.h

FORMS += \
    clienthandler.ui \
    databasemanager.ui \
    food.ui \
    foodrepository.ui \
    ordermanager.ui \
    orderpersistence.ui \
    restaurant.ui \
    restaurantdata.ui \
    restaurantrepository.ui \
    serverapp.ui \
    serverorder.ui \
    userrepository.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
