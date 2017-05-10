#ifndef MUUNNOS_H
#define MUUNNOS_H

#include <string>

class Muunnos {
public:
    Muunnos() ;
    double tee_muunnos(double arvo) ;
    void aseta_kertoimet(double kerroin, double offset);
    double hae_kerroin() ;
    double hae_offset() ;
    //~Muunnos() ;
private:
    double kerroin_ ;
    double offset_ ;
};

#endif // MUUNNOS_H
