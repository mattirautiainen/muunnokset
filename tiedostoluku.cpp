#include "tiedostoluku.h"

// Hakee tiedostosta muunnokset ja tallentaa ne listat-olioon.
bool hae_tiedot(string tiedostonnimi, Listat &listat) {
    fstream fs ;
    fs.open(tiedostonnimi) ;
    if(!fs) {
        cerr << "Virhe syotetiedoston lukemisessa: avaaminen epaonnistui."
             << endl ;
        return false ;
    }

    string rivi ;

    while(getline(fs,rivi)) {
        if(!rivi.empty())
        {
            rivi = poista_valilyonnit(rivi) ;
            if(rivi.at(0) == '#')
            {
                continue ;
            }

            vector<string> kentat ;
            vector<string> erottimet ;
            if(rivi.find('+') != string::npos) {
                erottimet = {"<=","*", "+"};
            }
            else if(rivi.find('-') != string::npos) {
                erottimet = {"<=","*","-"} ;
            }
            else {
                erottimet = {"<=","*"} ;
            }
            if(paloittele_rivi(rivi,erottimet,kentat)) {

                if(not virheeton(kentat))
                {
                    cerr << "Virhe syotetiedoston lukemisessa: virheellinen rivi."
                         << endl ;
                    return false ;
                }
                string kohdeyksikko = kentat[0] ;
                string lahtoyksikko = kentat[4] ;
                double kerroin = muuta_string_doubleksi(kentat[2]) ;
                double offset = 0 ;
                if(kentat.size() == 7 and kentat[5] == "+")
                {
                    offset = muuta_string_doubleksi(kentat[6]) ;
                }
                else if(kentat.size() == 7 and kentat[5] == "-") {
                    offset = -muuta_string_doubleksi(kentat[6]) ;
                }

                if(!listat.lisaa_listoihin(kohdeyksikko,lahtoyksikko,
                                           kerroin,offset)) {
                    cerr << "Virhe syotetiedoston lukemisessa: "
                         << "tiedostoa ei voitu lukea." << endl ;
                    return false ;
                }
            }
            else {
                cerr << "Virhe syotetiedoston lukemisessa: virheellinen rivi."
                     << endl ;
                return false ;
            }

        }
    }

    return true ;
}


// Tarkasta yhden rivin virheettomyys.
bool virheeton(vector<string> kentat) {
    if(kentat.size() != 5 and kentat.size() != 7) {
        return false ;
    }

    string sallitut = "/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ;
    string kohdeyksikko = kentat.at(0) ;
    for(unsigned i = 0 ; i < kohdeyksikko.size() ; ++i) {
        if(sallitut.find(kohdeyksikko.at(i)) == string::npos){
            return false ;
        }
    }
    string lahtoyksikko = kentat.at(4) ;
    for(unsigned i = 0 ; i < lahtoyksikko.size() ; ++i) {
        if(sallitut.find(lahtoyksikko.at(i)) == string::npos){
            return false ;
        }
    }

    if(lahtoyksikko == kohdeyksikko) {
        return false ;
    }

    if(kentat.at(1) != "<=" and kentat.at(3) != "*") {
        return false ;
    }

    if(!onko_double_string(kentat.at(2))) {
        return false ;
    }

    if(kentat.size() == 7) {
        if(kentat.at(5) != "+" and kentat.at(5) != "-") {
            return false ;
        }
        if(!onko_double_string(kentat.at(6))) {
            return false ;
        }
    }
    return true ;
}
