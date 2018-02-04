#include <QGuiApplication>
#include <QApplication>
#include <QWidget>
#include <QTest>
#include "silnik.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Silnik x;
    x.oknoPowitalne();
    QTest::qWait(2000);
    x.widok.close();
    x.otworz();

    return app.exec();
}

