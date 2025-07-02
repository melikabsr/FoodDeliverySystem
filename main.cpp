/*
#include <QApplication>
#include "MainWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();  // این خیلی مهمه!

    return app.exec();  // تا زمانی که یکی از ویجت‌ها باز هست، برنامه بسته نشه
}



#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(600, 400);
    window.setWindowTitle("🚀 Food Delivery Client");
    window.show();

    return app.exec();
}
*/




#include "DebugTestWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DebugTestWindow window;
    window.show();

    return app.exec();
}
