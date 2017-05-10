#ifndef TIEDOSTOLUKU_H
#define TIEDOSTOLUKU_H

#include <fstream>
#include <iostream>
#include <string>

#include "merkkijonoapu.h"
#include "listat.h"

using namespace std;

bool hae_tiedot(string tiedostonnimi, Listat &listat) ;
bool virheeton(vector<string> kentat) ;

#endif // TIEDOSTOLUKU_H
