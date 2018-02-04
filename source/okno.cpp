#include "okno.h"

Okno::Okno(){
    this->setWindowTitle(tr("Projekt!"));
    this->setMinimumSize(800,570);
    this->setWindowIcon(QIcon(":/obrazki/ikona.png"));

    _zadanie= new QAction(tr("Dodaj Zadanie"),this);
    _manzadanie= new QAction(tr("Zarzadzaj Zadaniami"),this);
    _opis= new QAction(tr("O Programie"),this);
    _optymalizuj= new QAction(tr("Utwórz wykres"), this);
    _reset= new QAction(tr("Zacznij od nowa"), this);
    _wykonaj= new QAction(tr("Rozpocznij algorytm"), this);

    _dodaj= new OknoDodawania;
    _scena= new QGraphicsScene(this);
    _widok= new QGraphicsView(_scena);
    _szablon= new Wykres;

    connect(_zadanie, SIGNAL(triggered()),this,SLOT(dodajZadanie()));
    connect(_manzadanie, SIGNAL(triggered()),this,SLOT(dodajZadanie()));
    connect(_opis, SIGNAL(triggered()), this,SLOT(opis()));
    connect(_optymalizuj,SIGNAL(triggered()),this,SLOT(utworz()));
    connect(_reset,SIGNAL(triggered()),this,SLOT(wyczysc()));
    connect(_wykonaj, SIGNAL(triggered()),this,SLOT(algorytm()));

    _dodaj->hide();

    _bar= addToolBar(tr("Pasek narzędzi"));
    _bar->addAction(_zadanie);
    //_bar->addAction(_manzadanie);
    _bar->addAction(_optymalizuj);
    _bar->addAction(_wykonaj);
    _bar->addAction(_reset);
    _bar->addAction(_opis);

    this->setCentralWidget(_widok);
    _scena->addItem(_szablon);

    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++){
            macierz_T[i][j]=0;
            macierz_Y[i][j]=0;
            macierz_V[i][j]=0;
        }
    for(int i=0;i<8;i++)
        przesunieciaZad[i]=0;
    Cmax=0;
    dlugoscSigma=1;
    Vmax=0;
    Vmin=100;
    zbiorOmega.clear();
    utworzonoWykres=false;
    zakonczonoAlgorytm=false;
    aktualnyproc=1;
}

void Okno::dodajZadanie(){
    _dodaj->show();
    _dodaj->activateWindow();
}

//Metoda odpowiedzialna za oczyszczenie, a następnie
//utworzenie wejściowego środowiska dla użytkownika.
void Okno::utworz()
{
    if(zakonczonoAlgorytm==false){
        utworzonoWykres=true;
        _scena->removeItem(T);
        _scena->removeItem(Y);
        _scena->removeItem(V);
        _scena->removeItem(tekstCmax);
        _scena->removeItem(tekstVmax);
        _scena->removeItem(tekstVmin);
        _scena->removeItem(tekstSigma);
        _scena->removeItem(tekstOmega);
        zbiorOmega.clear();
        for(int i=0;i<8;i++)
            przesunieciaZad[i]=0;
        zbiorZadan=_dodaj->_zadania;
        for(int i=0; i<zbiorZadan.size(); i++){
            _scena->addItem(zbiorZadan[i]);
        }
        wyznaczCmax();
        obliczT();
        obliczY();
        obliczV();
        obliczOmega();
        pokazTeksty();
        _optymalizuj->setText(tr("Zaktualizuj wykres"));
        _scena->update();
    }else{
        QMessageBox tmp;
        tmp.setText(tr("Najpierw musisz usunąć stary wynik by rozpocząć nowy projekt"));
        tmp.exec();
    }
}

//Metoda odpowiada za usunięcie poprzednich działań użytkownika:
//- zeruje wartości zmiennych
//- kasuje listy zdarzeń ze wszystkich zbiorów
//- usuwa wszystkie obiekty graficzne z wyjątkiem wykresu.
void Okno::wyczysc(){
    Cmax=0;
    Vmax=0;
    Vmin=100;
    dlugoscSigma=1;
    aktualnyproc=1;
    utworzonoWykres=false;
    zakonczonoAlgorytm=false;
    for(int i=0;i<8;i++)
        przesunieciaZad[i]=0;
    for(QVector<Zdarzenie*>::Iterator i= zbiorZadan.begin(); i!=zbiorZadan.end(); i++){
        _scena->removeItem(*i);
    }
    for(QVector<Zdarzenie*>::Iterator i= zbiorRozwiazan.begin(); i!=zbiorRozwiazan.end(); i++){
        _scena->removeItem(*i);
    }
    _dodaj->_zadania.clear();
    zbiorZadan.clear();
    zbiorRozwiazan.clear();
    zbiorOmega.clear();
    _dodaj->_zadania.clear();
    _dodaj->setWindowTitle(tr("ILOŚĆ ZADAŃ: 0"));
    _scena->removeItem(T);
    _scena->removeItem(Y);
    _scena->removeItem(V);
    _scena->removeItem(tekstCmax);
    _scena->removeItem(tekstVmax);
    _scena->removeItem(tekstVmin);
    _scena->removeItem(tekstSigma);
    _scena->removeItem(tekstOmega);
    for(int i=0;i<6;i++)
        rozmiarMacierz[i]=0;
    for(int i=0;i<8;i++)
        przesunieciaZad[i]=0;
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++){
            macierz_T[i][j]=0;
            macierz_Y[i][j]=0;
            macierz_V[i][j]=0;
        }
    _optymalizuj->setText(tr("Utwórz wykres"));
    _scena->update();
    _dodaj->hide();
}

//Metoda wyświetla wszelkie teksty wyświetlające informacje.
void Okno::pokazTeksty(){
    tekstCmax=new Napis(-300,0,tr("Cmax=%1").arg(this->Cmax));
    tekstVmax=new Napis(-300,25,tr("Vmax=%1").arg(this->Vmax));
    tekstVmin=new Napis(-300,50,tr("Vmin=%1").arg(this->Vmin));
    tekstSigma=new Napis(-300,75,tr("Sigma=%1").arg(this->dlugoscSigma));
    tekstOmega=new Napis(-250,190,tr("Zbiór Omega: "));
    for(int i=0; i<zbiorOmega.size();i++){
        tekstOmega->zmienNapis(tr(" (%1,%2)=%3 ;").
             arg(zbiorOmega[i].first).
             arg(zbiorOmega[i].second).
             arg(macierz_V[zbiorOmega[i].first][zbiorOmega[i].second]));
    }
    _scena->addItem(tekstCmax);
    _scena->addItem(tekstVmax);
    _scena->addItem(tekstVmin);
    _scena->addItem(tekstSigma);
    _scena->addItem(tekstOmega);
    _scena->update();
    _widok->show();
}

//Metoda wylicza wartość Cmax (czas maksymalny).
void Okno::wyznaczCmax(){
    uint suma=0; //obecny czas (wyliczony)
    for(int i=0; i<8; i++){
        for(int j=0;j<zbiorZadan.size();j++){
        if(i==zbiorZadan[j]->procesor){
            suma+=zbiorZadan[j]->czas;
        }}
        if(Cmax<(int)suma){
            Cmax=suma;
        }
        suma=0;
    }}
//Metoda pomocnicza względem Cmax.*
void Okno::wyznaczCmaxZV(){
    int suma=0;
    int tmp=0;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
           suma+=macierz_V[i][j];
        }if(tmp<suma) tmp=suma;
    }
    Cmax=tmp;
}


//METODA OBLICZA MACIERZ T: m x n (czas poszczególnych zadań)
void Okno::obliczT(){ 
    uint tmp=0; //MAX procseora
    uint tmp2=0; //MAX zadania
    uint tmp3=0; //czas pomocniczy
    int tmp4=0; //przechowywanie przekształcenia QString -> int
    QString numer; //pomoc do przekształcenia nazwy zadania do numeru
    //Zerowanie macierzy T
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++){
            macierz_T[i][j]=0;
        }
    //tworzenie macierzy
    for(int i=0; i<zbiorZadan.size();i++){
        if(zbiorZadan[i]->nazwa!=". . ."){
            tmp3+=zbiorZadan[i]->czas;
            numer=zbiorZadan[i]->nazwa.at(1);
            tmp4=numer.toInt();
            macierz_T[zbiorZadan[i]->procesor-1][tmp4-1]+=tmp3;
            tmp3=0;
            if(tmp2<(uint)tmp4)
                tmp2=tmp4;
            if(tmp<zbiorZadan[i]->procesor)
                tmp=zbiorZadan[i]->procesor;
        }
    }
    pokazT(tmp,tmp2);
}
//Metoda odpowiedzialna za przedstawienie graficzne macierzy T.
void Okno::pokazT(int x, int y){
    QString tekst_tmp("MACIERZ T: ");
    rozmiarMacierz[0]=x;
    rozmiarMacierz[1]=y;
    T= new Macierz(x,y,250,-190,macierz_T,tekst_tmp);
    _scena->addItem(T);
    T->show();
}
//METODA OBLICZA MACIERZ Y: m x m (przestoje)
void Okno::obliczY(){
    uint tmp=0; //MAX procesora
    uint tmp2=0; //czas
    QString nazwa_tmp=". . ."; //QString pomocniczy do wyszukiwania po nazwie Z0
    //Zerowanie macierzy Y
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++){
            macierz_Y[i][j]=0;
        }
    //Wywolanie wyrownania macierzy Y
    this->wyrownajWykres();
    //tworzenie macierzy
    for(int i=0;i<zbiorZadan.size(); i++){
        if(zbiorZadan[i]->nazwa==nazwa_tmp){
            tmp2+=zbiorZadan[i]->czas;
            macierz_Y[zbiorZadan[i]->procesor-1][zbiorZadan[i]->procesor-1]+=tmp2;
            tmp2=0;
            if(tmp<zbiorZadan[i]->procesor)
            {
                tmp=zbiorZadan[i]->procesor;
            }
        }
    }
    pokazY(tmp,tmp);
}
//Metoda odpowiedzialna za przedstawienie graficzne macierzy Y.
void Okno::pokazY(int x, int y){
    QString tekst_tmp("MACIERZ Y: ");
    rozmiarMacierz[2]=x;
    rozmiarMacierz[3]=y;
    Y= new Macierz(x,y,250,-50,macierz_Y,tekst_tmp);
    _scena->addItem(Y);
    Y->show();
}
//Metoda wyrównująca wykres przestojami procesorów
void Okno::wyrownajWykres(){
    int suma=0;
    for(int n=0; n < rozmiarMacierz[1]; n++){
        suma=0;
        for(int i=0; i< zbiorZadan.size() ; i++){
            if(zbiorZadan[i]->procesor==n+1){
                suma+=zbiorZadan[i]->czas;
            }
        }
        if(suma < Cmax && Cmax-suma!=0){
            Zdarzenie *tmp= new Zdarzenie(n+1,Cmax-suma,tr(". . ."));
            zbiorZadan.append(tmp);
        }
    }
}
//Metoda wylicza wartości dla macierzy V.
void Okno::obliczV(){
    int k=0; //pomocnicza zmienna.
    std::copy(&macierz_T[0][0], &macierz_T[0][0]+100*100, &macierz_V[0][0]);
    //tworzenie macierzy V.
    for(int i=rozmiarMacierz[1]; i<100; i++){
        for(int j=0; j<50;j++){
           macierz_V[j][i]=macierz_Y[j][k];
        }
        k++;
    }
    rozmiarMacierz[4]=rozmiarMacierz[0];
    rozmiarMacierz[5]=rozmiarMacierz[1]+rozmiarMacierz[3];
    pokazV(rozmiarMacierz[4],rozmiarMacierz[5]);
}
//Metoda odpowiedzialna za przedstawienie graficzne macierzy V.
void Okno::pokazV(int x, int y){
    QString tekst_tmp("MACIERZ V: ");
    rozmiarMacierz[4]=x;
    rozmiarMacierz[5]=y;
    V= new Macierz(x,y,250,100,macierz_V,tekst_tmp);
    _scena->addItem(V);
    V->show();
}

//Metoda oblicza zbiór Omega oraz określa wartości Vmax, Vmin.
void Okno::obliczOmega(){
    /*
     * i - num procesora
     * j - num zadania
    */
    QList<int> banListaKolumn;
    QList<int> banListaWierszy;
    QPair<int,int> temp; //temp pomocniczy o wyszukiwania maximum z macierzy V
    int suma=0;
    //Określenie zbioru Omega punktów krytycznych.
    for(int j=0; j<rozmiarMacierz[1]; j++){
       for(int i=0; i<rozmiarMacierz[0]; i++){
           suma+=macierz_V[i][j];
       }
       if(suma==Cmax){
       for(int i=0; i<rozmiarMacierz[0]; i++){
           if(macierz_V[i][j]>0){
               zbiorOmega.append(qMakePair(i,j));
               break;
           }
       }
       }
       suma=0;
    }
    //Konfiguracja list zajętych kolumn i wierszy do określenia
    //punktów nie krytycznych w zbiorze Omega.
    for(int el=0; el<zbiorOmega.size(); el++){
        banListaKolumn.append(zbiorOmega[el].first);
        banListaWierszy.append(zbiorOmega[el].second);
    }
    //Sortowanie elementów list przechowujących niedostępne numery
    //kolumn oraz wierszy.
    qSort(banListaKolumn);
    qSort(banListaWierszy);
    //Dodanie elementów dodatnich do macierzy V które nie należą do
    //kolumn krytycznych.
    for(int i=0; i<rozmiarMacierz[4]; i++){
        temp.first=99;
        temp.second=99;
        for(int j=0; j<rozmiarMacierz[5]; j++){
            if(banListaKolumn.contains(i)==true || banListaWierszy.contains(j)==true) continue;
            else{
                if(macierz_V[i][j]>macierz_V[temp.first][temp.second]){
                    temp.first=i;
                    temp.second=j;
                }
            }
        }
        if(macierz_V[temp.first][temp.second]>0){
            zbiorOmega.append(qMakePair(temp.first,temp.second));
            banListaKolumn.append(temp.first);
            banListaWierszy.append(temp.second);
        }
    }
    banListaKolumn.clear();
    banListaWierszy.clear();
    //Wyszukanie zdarzeń Vmax [zdarzenie o najwższej wartości] oraz
    //zdarzenia Vmin [zdarzenie o najniższej wartości] w macierzy V.
    for(int i=0; i<zbiorOmega.size();i++){
        if(Vmax < macierz_V[zbiorOmega[i].first][zbiorOmega[i].second])
        {
            Vmax=macierz_V[zbiorOmega[i].first][zbiorOmega[i].second];
        }
        if(Vmin > macierz_V[zbiorOmega[i].first][zbiorOmega[i].second]
                && macierz_V[zbiorOmega[i].first][zbiorOmega[i].second]!=0)
        {
            Vmin=macierz_V[zbiorOmega[i].first][zbiorOmega[i].second];
        }
    }
}

//Metoda dodaje kolejne zadanie do rozwiązania.
void Okno::dodajElRozw(){
    //Dodanie poszczególnych zadań zbioru Omega do
    //zbioru rozwiązań w celu przedstawienia
    //graficznego na wykresie.
    for(int i=0; i<zbiorOmega.size(); i++){
        wsk= new Zdarzenie();
        if(dlugoscSigma==0) dlugoscSigma=1;
        wsk->czas=dlugoscSigma;
        wsk->nazwa=tr("Z%1").arg(zbiorOmega[i].second+1);
        if(zbiorOmega[i].second>=rozmiarMacierz[1])
            wsk->nazwa=tr(". . .");
        wsk->procesor=zbiorOmega[i].first+1;
        wsk->przesuniecie=przesunieciaZad[wsk->procesor];
        if(czyZawieraElRozw(*wsk)==true)
        {
            wsk->nazwa=tr(". . .");
            macierz_V[wsk->procesor][wsk->procesor]-=dlugoscSigma;
        }else{
            macierz_V[zbiorOmega[i].first][zbiorOmega[i].second]-=dlugoscSigma;
        }
        //aktualizowanie zmiennych i dodanie zadania wsk
        //do zbioru Rozwiązań.
        przesunieciaZad[wsk->procesor]+=dlugoscSigma;
        zbiorRozwiazan.append(wsk);
    }
}

void Okno::algorytm(){
    //Weryfikacja istnienia zdarzeń dla wykresu.
    this->czyUtworzonoWykres();
    //Wyczyszczenie listy zbioru zadań.
    if(zbiorZadan.isEmpty()==false){
        for(QVector<Zdarzenie*>::Iterator i= zbiorZadan.begin(); i!=zbiorZadan.end(); i++){
            _scena->removeItem(*i);
            }
        zbiorZadan.clear();
    }
    //WEJŚCIE ALGORYTM, WARUNEK WHILE
    while(Cmax>0 && dlugoscSigma>0)
    {
        //Oczyszczenie sceny.
        _scena->removeItem(V);
        _scena->removeItem(tekstCmax);
        _scena->removeItem(tekstOmega);
        _scena->removeItem(tekstVmax);
        _scena->removeItem(tekstVmin);
        _scena->removeItem(tekstSigma);
        _scena->update();

    //ALGORYTM:
        //Wyznaczanie długości uszeregowania częściowego.
        if(Cmax-Vmin>=Vmax){
            dlugoscSigma= Vmin;
            Cmax=Cmax-dlugoscSigma; //Zmniejszenie Cmax o wartosc Sigmy.
        }
        else //if(Cmax-Vmax>0)
        {
            dlugoscSigma= Cmax-Vmax;
            Cmax=Cmax-dlugoscSigma; //Zmniejszenie Cmax o wartosc Sigmy.
        }
        dodajElRozw();
        //Aktualizacja sceny (obiektów, tekstów, macierz).
        zbiorOmega.clear();
        pokazV(rozmiarMacierz[4], rozmiarMacierz[5]);
        obliczOmega();
        pokazTeksty();
        _scena->addItem(V);
        for(int i=0; i<zbiorRozwiazan.size(); i++){
            _scena->addItem(zbiorRozwiazan[i]);
        }
        _scena->update();
        QTest::qWait(350);
    }
    //Warunek negatywny oznaczający zakończenie pracy algorytmu
    //wyświetla okienko tekstowe z odpowiednią informacją.
     if(utworzonoWykres==true){
        QMessageBox tmp;
        tmp.setText(tr("Algorytm zakończył pracę"));
        zakonczonoAlgorytm=true;
        tmp.exec();
     }
}

//Metoda sprawdza, czy pojawiają się jakieś te same zadania
//w tym samym przesunięciu
bool Okno::czyZawieraElRozw(Zdarzenie &el){
    for(int i=0; i<zbiorRozwiazan.size(); i++){
        if(el.nazwa==zbiorRozwiazan[i]->nazwa && el.nazwa!=tr(". . .") &&
                zbiorRozwiazan[i]->przesuniecie==el.przesuniecie &&
                el.procesor!=zbiorRozwiazan[i]->procesor)
            return true;
    }return false;
}

void Okno::czyUtworzonoWykres(){
    if(utworzonoWykres==false){
        QMessageBox tmp;
        tmp.setText(tr("Najpierw musisz utworzyć wykres zanim uruchomisz algorytm!"));
        tmp.exec();
    }
}

void Okno::opis(){
    QMessageBox tmp;
    tmp.setText(tr(
"<b> O programie</b>: <br>"
"Program przedstawia działanie <i>\"Wyznaczania uszeregowania</i>"
"<i> optymalnego na podstawie znajomości rozwiązania problemu programowania liniowego.\"</i>"
"<br><br><b> O Autorze</b>: <br>"
"Michał Majewski "
""
"<br><br><br>Projekt wykonany na zajęcia <i>Projekt Indywidualny</i>, UKSW w Warszawie, 2016r"));

    tmp.exec();
}








