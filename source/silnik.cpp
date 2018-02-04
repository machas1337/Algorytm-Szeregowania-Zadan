#include "silnik.h"

Silnik::Silnik()
{
https://github.com/machas1337/Algorytm-Szeregowania-Zadan/tree/master/source
}
void Silnik::otworz(){
    glowne.show();
}

void Silnik::oknoPowitalne(){
    widok.setScene(&scena);
    widok.setFixedSize(680,550);
    scena.addItem(&item);
    item.setToolTip("ZAMKNIJ OKNO ABY KONTYNUOWAĆ");
    scena.update();
    widok.show();

}
