#include "zdarzenie.h"
#include "QtWidgets/QErrorMessage"
#include <QString>
#include "definicje.cpp"


Zdarzenie::Zdarzenie()
{
    czas=0;
    procesor=1;
    nazwa="Z0";
    przesuniecie=0;
}

Zdarzenie::Zdarzenie(uint _procesor, uint _czas){
    procesor=_procesor;
    czas=_czas;
}
Zdarzenie::Zdarzenie(uint _procesor, uint _czas, QString _nazwa){
    procesor=_procesor;
    czas=_czas;
    nazwa=_nazwa;
}

QRectF Zdarzenie::boundingRect() const{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

//Przeciążona metoda która w swojej definicji prócz samego rysowania
//również odpowiada za umiejscowienie zadania na wykresie.
//Zdarzenie samo określa miejsce położenia na podstawie trzech podstawowych zmiennych:
//Czas - ile miejsca potrzebuje, Procesor - w którym wierszy wykresu oraz
//Przesunięcie - mówiące ile czasu zajmowanych jest w danym wierszy przez inne zdarzenia
//wartość jest wyznaczona w jednostkach czasu.
void Zdarzenie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(PUNKT_ZERO_X+przesuniecie*ODLEGLOSC_CZAS,PUNKT_ZERO_YP+((procesor-1)*ODLEGLOSC_PROCESOR),RECT_SIZE_W*czas,RECT_SIZE_H);
    painter->drawText(PUNKT_ZERO_X+czas*(ODLEGLOSC_CZAS)/3+przesuniecie*ODLEGLOSC_CZAS, PUNKT_ZERO_YP+((procesor-1)*ODLEGLOSC_PROCESOR)-10, nazwa);

}




