#include <QCoreApplication>
#include "ServerApp.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ServerApp server;
    server.startServer(1234);
    return app.exec();
}




