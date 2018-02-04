#ifndef ZDARZENIE_H
#define ZDARZENIE_H

#include <QtGlobal>
#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include <QString>

class Zdarzenie: public QGraphicsItem
{
public:
    Zdarzenie();
    Zdarzenie(uint _procesor, uint _czas);
    Zdarzenie(uint _procesor, uint _czas, QString _nazwa);
    uint czas; //czas wykonania zadania dla procesora.
    uint procesor; //numer procesora
    uint przesuniecie; //przesuniecie obiektu by nie powodować kolizji
    QString nazwa; //nazwa zadania
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // ZDARZENIE_H
