#include "oknododawania.h"

OknoDodawania::OknoDodawania(QWidget *parent) : QWidget(parent)
{
    _przycisk= new QPushButton(tr("Dodaj"), this);
    _przycisk->setGeometry(QRect(QPoint(330, 140),QSize(50, 38)));
    this->setWindowTitle(tr("DODAWANIE ZADANIA"));
    this->setMaximumSize(380, 220);
    this->setVisible(true);
    utworz();
}
//Metoda tworzące okno dodawania Zdarzeń.
void OknoDodawania::utworz()
{   
    _linia1= new QSpinBox(this);
    _linia2= new QSpinBox(this);
    _linia3= new QSpinBox(this);
    _linia4= new QSpinBox(this);
    _info1= new QLabel(tr("Przypisanie zadania do procesora: "),this);
    _info2= new QLabel(tr("Ilość czasu dla zadania "),this);
    _info3= new QLabel(tr("Ilość procesorów: "),this);
    _info4= new QLabel(tr("Numer zadania: "),this);

    _linia2->setRange(1,10);
    _linia3->setRange(2,8);
    _linia1->setRange(1,_linia3->maximum());
    _linia4->setRange(0,9); //gdzie 0 oznacza przestoj
    _linia4->setValue(1);
    _linia4->setPrefix(tr("Z"));

    _info1->setGeometry(QRect(QPoint(15, 15),QSize(200, 30)));
    _linia1->setGeometry(QRect(QPoint(15, 50),QSize(100, 30)));
    _info2->setGeometry(QRect(QPoint(15, 85),QSize(200, 30)));
    _linia2->setGeometry(QRect(QPoint(15, 120),QSize(100, 30)));
    _info3->setGeometry(QRect(QPoint(210,85),QSize(200,30)));
    _linia3->setGeometry(QRect(QPoint(210,120),QSize(100,30)));
    _info4->setGeometry(QRect(QPoint(210,15),QSize(200,30)));
    _linia4->setGeometry(QRect(QPoint(210, 50),QSize(100,30)));

    connect(_przycisk, SIGNAL(pressed()), this, SLOT(przyciskDodaj()));
 //   connect(_linia3,SIGNAL(valueChanged(_linia3->value())), this, SLOT(maksZakres()));
    connect(_linia4, SIGNAL(valueChanged(int)), this, SLOT(podmienPrzestoj()));

    _info1->show();
    _linia1->show();
    _info2->show();
    _linia2->show();
//    _info3->show();
//    _linia3->show();
    _info4->show();
    _linia4->show();
    _przycisk->show();
}
//Metoda określająca działanie przycsiku potwierdzenia "Dodaj".
void OknoDodawania::przyciskDodaj(){
    _zadanie= new Zdarzenie;
    _zadanie->procesor=_linia1->value();
    _zadanie->czas=_linia2->value();
    if      (_linia4->value()==0) _zadanie->nazwa=tr(". . .");
    else     _zadanie->nazwa=tr("Z%1").arg(_linia4->value());

    //kontrola poprawności rysowania zadań
    for(int i=0; i<_zadania.size();i++){
        if(_zadanie->procesor==_zadania[i]->procesor)
            _zadanie->przesuniecie+=_zadania[i]->czas;
    }
    _zadania.push_back(_zadanie);
    _linia2->setValue(1);
    this->setWindowTitle(tr("ILOŚĆ ZADAŃ: %1").arg(_zadania.size()));
}
//Metoda określająca maksymalną liczbę dostępnych procesorów.
void OknoDodawania::maksZakres(){
    _linia1->setRange(1, _linia3->maximum());
}
//Informacja pojawiająca się po wybraniu Zadania "Z0" (przestój).
void OknoDodawania::podmienPrzestoj(){
    if(_linia4->value()==0){
        QWidget::setToolTip(tr("Pamiętaj, że zadanie o numerze <u>0</u> oznacza <b>PRZESTÓJ</b> dla procesora!"));
//    }else
//        QToolTip::hideText();
    }
}
