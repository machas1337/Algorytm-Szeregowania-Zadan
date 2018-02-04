#ifndef SILNIK_H
#define SILNIK_H
#include "zdarzenie.h"
#include "procesor.h"
#include "okno.h"
#include "oknostartowe.h"
#include <QVector>
#include <QtGlobal>
#include <QPainter>


class Silnik
{
public:
    Silnik();
    QVector<Zdarzenie> zdarzenia; //Zbiór zadań zdarzeń.
    QGraphicsScene scena; //Scena okna powitalnego.
    QGraphicsView widok; //Widok na scenę okna powitalnego.
    QPixmap uksw; //Grafika - logo UKSW.
    QGraphicsPixmapItem item;
    void otworz();
    void oknoPowitalne();
    uint procesory;
    Okno glowne;


};

#endif // SILNIK_H
