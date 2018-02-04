#ifndef WYKRES_H
#define WYKRES_H

#include <QPainter>
#include <QObject>
#include <QGraphicsItem>

class Wykres: public QGraphicsItem
{
public:
    Wykres();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

class Napis: public QGraphicsTextItem
{
public:
    //Współrzędne x,y określają punkt rozpoczęcia rysowania Napisu na scenie.
    int x;
    int y;
    QString nazwa;
    Napis(int _x, int _y, QString _nazwa);
    void zmienNapis(QString _napis); //Metoda służąca do dodawnaia napisu w obiekcie.
    void zamienNapis(QString _napis); //Metoda służąca do zmiany napisu w obiekcie.
    //Przeciążone metody śrdowiska służące do rysowania obiektów na scenie.
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

class Macierz: public QGraphicsItem
{
public:
    int x,y,px,py; //gdzie x,y - rozmiar macierzy, px,py: punkt początkowy macierzy
    int macierz[100][100];
    QString nazwa;
    Macierz(int _x, int _y, int _px, int _py, int _macierz[100][100], QString _nazwa);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // WYKRES_H
