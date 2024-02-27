#include <QApplication>
#include <QDebug>

#include "MiniDump.h"

int main(int argc, char *argv[])
{
    MiniDump::SetAutoDumpEnable(true);

    QApplication a(argc, argv);

    int* ptr = nullptr;
    *ptr = 5;

    return a.exec();
}
