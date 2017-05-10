#ifndef LISTA_H
#define LISTA_H

#include <string>
using namespace std;

// Tietorakenteet, johon muunnokset talletetaan ovat linkitettyja listoja.
// Mikali muunnos joidenkin kahden yksikon valilla on mahdollinen, molemmat
// yksikot kuuluvat samaan listaan. Mikali muunnos kahden tiedossa olevan
// yksikon valilla ei ole mahdollinen, ne kuuluvat eri listoihin. Yksi
// yksikko esiintyy tietorakenteessa vain kerran ja kuuluu vain ja
// ainoastaan yhteen listaan.

// Listassa olevat alkiot muodostavat ketjun, jonka avulla pystyy laskemaan
// muunnoksen minka tahansa kahden listassa olevan yksikon valilla.
// Listoihin lisattaessa yksikoita alkioille lasketaan oikeat muutoskertoimet.

// Yksi Yksikko-struktuuri sisaltaa yksikon nimen seka muunnosarvot seuraavaan
// yksikkoon siten, etta nykyisen yksikon kerroin ja offset muodostavat
// muunnoksen seuraavaan yksikkoon kaavalla Y = kerroin*X + offset, jossa
// X on nykyinen yksikko ja Y on seuraava yksikko ja kerroin ja offset ovat
// nykyisessa yksikossa olevia kertoimia.

struct Yksikko {
    string nimi ;
    double kerroin ;
    double offset ;
    Yksikko *seuraava ;
    Yksikko *edellinen ;
};

class Lista {
public:

    Lista() ;
    void tuhoa_lista() ;
    void tyhjenna() ;
    bool hae_yksikko(string nimi, Yksikko *&yksikko) ;
    bool lisaa_muunnos(Yksikko* &edell, string nimi,
                       double kerroin, double offset) ;
    bool tee_muunnos(string kohdeyksikko, string lahtoyksikko,
                       double arvo, double &tulos) ;
    bool muunnos_loytyy(string kohdeyksikko, string lahtoyksikko) ;
    bool lisaa_ensimmainen(string kohdeyksikko, string lahtoyksikko,
                           double kerroin, double offset) ;
    bool hae_kertoimet(string kohdeyksikko, string lahtoyksikko,
                          double &kerroin, double &offset) ;
    void tulosta() ;
private:

    Yksikko *ensimmainen_ ;
};

#endif // LISTA_H
