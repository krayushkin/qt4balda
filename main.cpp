#include "game.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game w;
    w.show();
    return a.exec();
}
