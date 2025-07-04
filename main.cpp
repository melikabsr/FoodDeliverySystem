

#include "ClientDatabaseManager.h"
#include <QApplication>
#include "MainWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ClientDatabaseManager::instance().openDatabase();
    ClientDatabaseManager::instance().setupTables();

    MainWindow w;
    w.show();
    return app.exec();
}
