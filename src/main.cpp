#include "mainwindow.h"

#include <ctime>
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QFile style("style.css");
    style.open(QIODevice::ReadOnly);

    QApplication a(argc, argv);
    a.setStyleSheet(style.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}

