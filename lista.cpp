#include "lista.h"
#include <iostream>

Lista::Lista() : ensimmainen_{0} {
}


// Poistaa listan alkiot
void Lista::tuhoa_lista() {
    Yksikko *poistettava = ensimmainen_ ;
    while(poistettava != nullptr) {
        Yksikko* seuraava = poistettava->seuraava ;
        delete poistettava ;
        poistettava = seuraava ;
    }
}

// Etsii yksikon tai asettaa sen nullptr jos yksikkoa ei loydy
bool Lista::hae_yksikko(string nimi, Yksikko* &yksikko) {
    yksikko = ensimmainen_ ;
    while(yksikko != nullptr) {
        if(yksikko->nimi == nimi) {
            return true ;
        }
        yksikko = yksikko->seuraava ;
    }
    return false ;
}

void Lista::tyhjenna() {
    ensimmainen_ = nullptr ;
}

// Lisaa muunnoksen listaan
bool Lista::lisaa_muunnos(Yksikko* &edell, string nimi,
                           double kerroin, double offset) {
    Yksikko *lisattava = nullptr ;
    try {
        lisattava = new Yksikko ;
    } catch(...) {
        return false ;
    }

    lisattava->nimi = nimi ;
    lisattava->kerroin = edell->kerroin / kerroin ;
    lisattava->offset = edell->offset - lisattava->kerroin*offset;
    lisattava->seuraava = edell->seuraava ;
    lisattava->edellinen = edell ;
    if(lisattava->seuraava != nullptr) {
        lisattava->seuraava->edellinen = lisattava ;
    }

    edell->kerroin = kerroin ;
    edell->offset = offset ;
    edell->seuraava = lisattava ;
    return true ;
}

// Tekee uuden listan
bool Lista::lisaa_ensimmainen(string kohdeyksikko, string lahtoyksikko,
                              double kerroin, double offset) {

    Yksikko *lahto = nullptr ;
    try {
        lahto = new Yksikko ;
    } catch(...) {
        return false ;
    }
    Yksikko *kohde = nullptr ;
    try {
        kohde = new Yksikko ;
    } catch(...) {
        return false ;
    }

    lahto->nimi = lahtoyksikko ;
    lahto->kerroin = kerroin ;
    lahto->offset = offset ;
    lahto->edellinen = nullptr ;
    lahto->seuraava = kohde ;

    kohde->nimi = kohdeyksikko ;
    kohde->kerroin = 0 ;
    kohde->offset = 0 ;
    kohde->edellinen = lahto ;
    kohde->seuraava = nullptr ;

    ensimmainen_ = lahto ;
    return true ;
}

// Palauttaa true, jos muunnos kahden yksikon valilla loytyy listasta
bool Lista::muunnos_loytyy(string kohdeyksikko, string lahtoyksikko) {
    Yksikko *yksikko = ensimmainen_ ;
    bool kohde_loytyi = false ;
    bool lahto_loytyi = false ;
    while(yksikko != nullptr) {
        if(yksikko->nimi == kohdeyksikko) {
            kohde_loytyi = true ;
        }
        if(yksikko->nimi == lahtoyksikko) {
            lahto_loytyi = true ;
        }
        if(kohde_loytyi and lahto_loytyi) {
            return true ;
        }
        yksikko = yksikko->seuraava ;
    }
    return false ;
}

// Tekee muunnoksen kahden yksikon valilla. Tulos tallentuu viiteparametrina.
bool Lista::tee_muunnos(string kohdeyksikko, string lahtoyksikko,
                           double arvo, double &tulos) {
    Yksikko* yksikko = ensimmainen_ ;
    double kerroin = 1 ;
    double offset = 0 ;
    if(kohdeyksikko == lahtoyksikko) {
        tulos = kerroin*arvo + offset ;
        return true ;
    }
    while(yksikko != nullptr) {
        if(yksikko->nimi == kohdeyksikko or yksikko->nimi == lahtoyksikko) {
            while(yksikko != nullptr) {
                kerroin = kerroin*yksikko->kerroin ;
                offset = offset*yksikko->kerroin + yksikko->offset ;
                yksikko = yksikko->seuraava ;

                if(yksikko->nimi == lahtoyksikko) {
                    tulos = 1/kerroin*arvo - offset/kerroin ;
                    return true ;
                }
                else if(yksikko->nimi == kohdeyksikko) {
                    tulos = kerroin*arvo + offset ;
                    return true ;
                }
            }
        }
        yksikko = yksikko->seuraava ;
    }
    return false ;
}

bool Lista::hae_kertoimet(string kohdeyksikko, string lahtoyksikko,
                             double &kerroin, double &offset) {
    Yksikko* yksikko = ensimmainen_ ;
    kerroin = 1 ;
    offset = 0 ;
    if(kohdeyksikko == lahtoyksikko) {
        return true ;
    }
    while(yksikko != nullptr) {
        if(yksikko->nimi == kohdeyksikko or yksikko->nimi == lahtoyksikko) {
            while(yksikko != nullptr) {
                kerroin = kerroin*yksikko->kerroin ;
                offset = offset*yksikko->kerroin + yksikko->offset ;
                yksikko = yksikko->seuraava ;

                if(yksikko->nimi == lahtoyksikko) {
                    return true ;
                }
                else if(yksikko->nimi == kohdeyksikko) {
                    return true ;
                }
            }
        }
        yksikko = yksikko->seuraava ;
    }
    return false ;
}

