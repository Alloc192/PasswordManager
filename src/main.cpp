#include "mainwindow.h"

#include <ctime>
#include <QApplication>
#include <QFile>

#include "Tests/testencoder.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QFile style("style.css");
    style.open(QIODevice::ReadOnly);
    QTest::qExec(new TestEncoder);
    QApplication a(argc, argv);
    a.setStyleSheet(style.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}

