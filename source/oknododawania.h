#ifndef OKNODODAWANIA_H
#define OKNODODAWANIA_H

#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QToolTip>
#include "zdarzenie.h"

class OknoDodawania : public QWidget
{
    Q_OBJECT
public:
    explicit OknoDodawania(QWidget *parent = 0); //Konstruktor jawny.
    //Pola tekstowe z informacjami.
    QLabel *_info1; //procesor
    QLabel *_info2; //czas
    QLabel *_info3; //ilość procesorów
    QLabel *_info4; //zadania i przestój
    //Pola wybierania wartości przez użytkownika.
    QSpinBox *_linia1; //procesor
    QSpinBox *_linia2; //czas
    QSpinBox *_linia3; //ilość procesorów
    QSpinBox *_linia4; //zadania i przestój
    QPushButton *_przycisk; //Przycisk potwierdzenia.
    Zdarzenie *_zadanie;
    QVector<Zdarzenie*> _zadania; //Zbiór nowoutworzonych zadań.
    void utworz();
public slots:
    void przyciskDodaj();
    void maksZakres();
    void podmienPrzestoj();
};
#endif // OKNODODAWANIA_H
