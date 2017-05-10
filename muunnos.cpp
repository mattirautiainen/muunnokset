#include "muunnos.h"

Muunnos::Muunnos() : kerroin_{0}, offset_{0} {
}

double Muunnos::tee_muunnos(double arvo) {
    double muunnos = arvo*kerroin_+offset_ ;
    return muunnos ;
}

void Muunnos::aseta_kertoimet(double kerroin, double offset) {
    kerroin_ = kerroin ;
    offset_ = offset ;
}

double Muunnos::hae_kerroin() {
    return kerroin_ ;
}

double Muunnos::hae_offset() {
    return offset_ ;
}
