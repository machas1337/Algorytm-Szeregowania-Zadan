#include "silnik.h"

Silnik::Silnik()
{

}
void Silnik::otworz(){
    glowne.show();
}

void Silnik::oknoPowitalne(){
    widok.setScene(&scena);
    widok.setFixedSize(680,550);
    uksw.load(":/obrazki/uksw_logo.png");
    item.setPixmap(uksw);
    scena.addItem(&item);
    item.setToolTip("ZAMKNIJ OKNO ABY KONTYNUOWAĆ");
    scena.update();
    widok.show();

}
