#include "syssec.h"
#include <QApplication>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SysSec w;
    w.show();

    return a.exec();
}
