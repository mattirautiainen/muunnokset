#include "listat.h"
#include <iostream>

Listat::Listat() {
}

Listat::~Listat() {
    for(unsigned i = 0 ; i < listat_.size() ; ++i) {
        Lista lista = listat_.at(i) ;
        lista.tuhoa_lista() ;
    }
}

// Lisaa muunnoksen listaan, yhdistaa kaksi listaa, tekee uuden listan.
// tai tarkastaa samassa listassa olevan muunnoksen patevyyden.
bool Listat::lisaa_listoihin(string kohdeyksikko, string lahtoyksikko,
                      double kerroin, double offset) {
    int kohdelistanum = -1 ;
    int lahtolistanum = -1 ;
    Yksikko *kohde = nullptr ;
    etsi_listoista(kohdeyksikko,kohdelistanum,kohde) ;
    Yksikko *lahto = nullptr ;
    etsi_listoista(lahtoyksikko,lahtolistanum, lahto) ;

    // lahtoyksikko ja kohdeyksikko loytyy jo listoista
    if(kohdelistanum >= 0 and lahtolistanum >= 0) {
        // lahtoyksikko ja kohdeyksikko samassa listassa, tarkasta kertoimet
        if(lahtolistanum == kohdelistanum) {
            double kerr = 0 ;
            double off = 0 ;
            if(listat_[kohdelistanum].hae_kertoimet(kohdeyksikko,lahtoyksikko,
                                                    kerr,off)) {
                if(kerr != kerroin or off != offset) {
                    return false ;
                }
            }
        }
        // lahtoyksikko ja kohdeyksikko eri listoissa, yhdista listat
        else {
            yhdista_listat(kohde,lahto,kerroin,offset) ;
            listat_[kohdelistanum].tyhjenna() ;
            listat_.erase(listat_.begin() + kohdelistanum) ;
        }
    }
    // pelkka kohdeyksikko loytyy listoista, lisaa lahtoyksikko listaan
    else if(kohdelistanum >= 0) {
        if(!listat_[kohdelistanum].lisaa_muunnos(kohde,lahtoyksikko,
                                             1/kerroin,-offset/kerroin)) {
            return false ;
        }
    }
    // pelkka lahtoyksikko loytyy listoista, lisaa kohdeyksikko listaan
    else if(lahtolistanum >= 0) {
        if(!listat_[lahtolistanum].lisaa_muunnos(lahto,kohdeyksikko,
                                             kerroin,offset)) {
            return false ;
        }

    }
    // kohdeyksikkoa tai lahtoyksikkoa ei loydy listoista, tee uusi lista
    else {
        Lista lista ;
        if(!lista.lisaa_ensimmainen(kohdeyksikko,lahtoyksikko,kerroin,offset)) {
            return false ;
        }
        listat_.push_back(lista);
    }
    return true ;
}

// Etsii muunnoksen listoista ja palauttaa true, mikali se loytyy
// Tulos tallentuu viiteparametrina.
bool Listat::hae_muunnos(string kohdeyksikko, string lahtoyksikko,
                         double arvo, double &tulos) {
    for(unsigned i = 0 ; i < listat_.size() ; ++i) {
        Lista lista = listat_[i] ;
        if(lista.muunnos_loytyy(kohdeyksikko,lahtoyksikko)) {
            if(lista.tee_muunnos(kohdeyksikko,lahtoyksikko,arvo,tulos)) {
                return true ;
            }
        }
    }
    return false ;
}

// Etsii yksikon listoista ja palauttaa true jos se loytyy.
// Listan paikka listavektorissa tallentuu viiteparametrina
bool Listat::etsi_listoista(string yksikonnimi, int &listanum,
                            Yksikko* &yksikko) {
    for(unsigned i = 0 ; i < listat_.size() ; ++i) {
        Lista lista = listat_[i] ;
        if(lista.hae_yksikko(yksikonnimi, yksikko)) {
            listanum = i ;
            return true ;
        }
    }

    return false ;
}

// Yhdistaa kaksi eri listaa siten, etta listan, jossa kohdeyksikko sijaitsee,
// ensimmainen alkio liittyy lahtoyksikon listan viimeisen alkio peraan
// asianmukaisilla muunnoskertoimilla.
void Listat::yhdista_listat(Yksikko *kohde, Yksikko *lahto,
                            double kerroin, double offset) {

    Yksikko *laskettava = lahto ;

    double kerr = 1 ;
    double off = 0 ;
    while(laskettava->seuraava != nullptr) {
        off = off*laskettava->kerroin + laskettava->offset ;
        kerr = kerr*laskettava->kerroin ;
        laskettava = laskettava->seuraava ;
    }
    Yksikko *liityttava = laskettava ;

    kerroin = kerroin/kerr ;
    offset = offset - off*kerroin  ;
    kerr = 1 ;
    off = 0 ;

    laskettava = kohde ;

    while(laskettava->edellinen != nullptr) {
        kerr = kerr/laskettava->edellinen->kerroin ;
        off = (off - laskettava->edellinen->offset )
                / laskettava->edellinen->kerroin ;
        laskettava = laskettava->edellinen ;
    }

    laskettava->edellinen = liityttava ;

    kerroin = kerr*kerroin ;
    offset = off + offset*kerr ;
    liityttava->kerroin = kerroin;
    liityttava->offset = offset;
    liityttava->seuraava = laskettava ;
}

void Listat::tulosta() {
    cout << listat_.size() << endl ;
    for(unsigned i = 0 ; i < listat_.size() ; ++i) {
        Lista lista = listat_[i] ;
        cout << i << endl ;
        lista.tulosta() ;
        cout << endl ;
    }
}




