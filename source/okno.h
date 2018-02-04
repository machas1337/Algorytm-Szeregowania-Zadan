#ifndef OKNO_H
#define OKNO_H

#include <QtGui>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QList>
#include <QSet>
#include <QTest>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "procesor.h"
#include "zdarzenie.h"
#include "oknododawania.h"
#include "wykres.h"


class Okno:public QMainWindow
{
    Q_OBJECT
public:
    Okno();
    uint zbiorProcesorow; //Zbiór wykorzystanych procesorów przez użytkownika.
    QVector<Zdarzenie*> zbiorZadan; //Zbiór zadań wejściowych (podaje użytkownik).
    QVector<Zdarzenie*> zbiorRozwiazan; //Zbiór zadań wyjściowych (rozwiązanie algorytmu).
    OknoDodawania *_dodaj; //Wskaźnik na obiekt Okna dodawania Zdarzeń.
    QGraphicsScene *_scena; //Wskaźnik na obiekt przedstawiający scenę.
    Wykres *_szablon; //Wskaźnik na obiekt przedstawiający wykres na scenie.
    QGraphicsView *_widok; //Wskaźnik na obiekt przedstawiająćy widok na scenę.
    bool utworzonoWykres; //Zmienna pomocnicza, określa czy wykres utworzono ze zdarzeniami.
    bool zakonczonoAlgorytm; //Zmienna pomocnicza informująca o zakończeniu pracy algorytmu
public:
    //Obiekty tekstowe rysowane na scenie.
    Napis *tekstCmax;
    Napis *tekstVmax;
    Napis *tekstVmin;
    Napis *tekstSigma;
    Napis *tekstOmega;
    //Zdarzenia szczególne.
    Zdarzenie *wsk;
    //Zmienne szczególne.
    int Cmax;
    int Vmax, Vmin;
    int dlugoscSigma;
    int aktualnyproc;
    //Obiekty reprezentujące prezentacje graficzne poszczególnych Macierz.
    Macierz *T;
    Macierz *Y;
    Macierz *V;
    //Kolejne macierze przechowujące wartości liczbowe.
    int macierz_T[100][100];
    int macierz_Y[100][100];
    int macierz_V[100][100];
    //Tablica pomocnicza przechowujące kolejne rozmiary Macierz.
    int rozmiarMacierz[6]; //[0,1] -T   [2,3] -Y  [4,5] -V.
    int przesunieciaZad[8]; //tablica przechowująca przesunięcia
    QVector<QPair<int,int>> zbiorOmega;
    //Kolejne metody, opisane zostały przy definicjach.
    void dodajElRozw();
    bool czyZawieraElRozw(Zdarzenie &el);
    void wyznaczCmax();
    void wyznaczCmaxZV();
    void obliczOmega();
    void obliczT();
    void obliczY();
    void obliczV();
    void pokazT(int x, int y); //x,y - rozmiar tabeli
    void pokazY(int x, int y);
    void pokazV(int x, int y);
    void pokazTeksty();
private slots:
    void dodajZadanie();
    void opis();
    void utworz();
    void wyczysc();
    void algorytm();
    void czyUtworzonoWykres();
    void wyrownajWykres();
private:
    //Wskaźniki na przyciski menu które sterują programem.
    QAction *_zadanie;
    QAction *_manzadanie;
    QAction *_procesor;
    QAction *_wykonaj;
    QAction *_manprocesor;
    QAction *_opis;
    QAction *_optymalizuj;
    QAction *_reset;
    QToolBar *_bar;
    QMenu *_menuProcesorow;
    QMenu *_menuZadan;

};

#endif // OKNO_H
