#include "caculate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Caculate w;
    w.show();
    return a.exec();
}
