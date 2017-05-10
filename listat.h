#ifndef LISTAT_H
#define LISTAT_H

#include "lista.h"
#include <vector>

class Listat {
public:
    Listat() ;
    ~Listat() ;
    void tuhoa() ;
    bool lisaa_listoihin(string kohdeyksikko, string lahtoyksikko,
                          double kerroin, double offset) ;
    bool hae_muunnos(string kohdeyksikko, string lahtoyksikko,
                     double arvo, double &tulos) ;
    void tulosta() ;
private:
    bool etsi_listoista(string yksikonnimi, int &listanum, Yksikko* &yksikko) ;
    void yhdista_listat(Yksikko *kohde, Yksikko *lahto,
                        double kerroin, double offset) ;

    vector<Lista> listat_ ;

};

#endif // LISTAT_H
