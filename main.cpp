#include <QApplication>
#include "MainWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();  // این خیلی مهمه!

    return app.exec();  // تا زمانی که یکی از ویجت‌ها باز هست، برنامه بسته نشه
}
