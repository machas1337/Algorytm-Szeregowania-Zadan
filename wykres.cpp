#include "wykres.h"

Wykres::Wykres()
{

}

QRectF Wykres::boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }

void Wykres::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        //główne linie
        painter->drawLine(-200,100 ,200,100);
        painter->drawLine(-200,100 ,-200,-130);
        //X i Y
        painter->drawText(200,115,QObject::tr("Czas"));
        painter->drawText(-245,-130,QObject::tr("Procesor"));
        //przedział procesorów
        for(int i=1; i<=9; i++){
            painter->drawLine(-200,-150+(250/9)*i, -215, -150+(250/9)*i);
            if(i!=9)painter->drawText(-220,-130+(250/9)*i, QObject::tr("%1").arg(9-i));
        }
        //przedział czasu
        for(int i=1; i<=10; i++){
            painter->drawLine(-200+i*(400/11),100 ,-200+i*(400/11),115);
            painter->drawText(-200+i*(400/11),125, QObject::tr("%1").arg(i));
        }

    }

//////////////////////////////////////////////////
//////////////////////////////////////////////////

Macierz::Macierz(int _x, int _y, int _px, int _py, int _macierz[100][100], QString _nazwa){
    //Znaczenie punktów w wykres.h.
    x=_x;
    y=_y;
    px=_px;
    py=_py;
    std::copy(&_macierz[0][0], &_macierz[0][0]+100*100, &macierz[0][0]);
    nazwa=_nazwa;
}

QRectF Macierz::boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }
void Macierz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawText(px,py-10,nazwa);
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            painter->drawText(px+j*15,py+i*15,QString::number(macierz[i][j]));
        }
    }


}

/////////////////////////////////////////////////////
//////////////////////////////////////////////////////

Napis::Napis(int _x, int _y, QString _nazwa){
    x=_x;
    y=_y;
    nazwa=_nazwa;
}
void Napis::zmienNapis(QString _napis){
    nazwa+=_napis;
}
void Napis::zamienNapis(QString _napis){
    nazwa=_napis;
}

QRectF Napis::boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }
void Napis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
       painter->drawText(x,y,nazwa);
    }
