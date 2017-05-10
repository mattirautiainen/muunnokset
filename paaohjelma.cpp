//*************************************************//
// Älä muuta rivejä, jotka ovat tämän rivin        //
                                                   //
   #ifdef SOURCEDIR                                //
     #include <unistd.h>                           //
     const int cd_status{ chdir(SOURCEDIR) };      //
   #endif                                          //
                                                   //
// ja tämän rivin välissä. Nämä koodirivit         //
// liittyvät siihen, että ohjelmaa suoritettaessa  //
// sen työkansio on sama kansio, jossa lähdekoodi  //
// sijaitsee: jos testisyötetiedostot ovat samassa //
// kansiossa, ne voi avata luettavaksi pelkällä    //
// tiedoston nimellä, kuten luentomonisteessa on   //
// kuvattu.  Tätä ratkaisua ei ole testattu kuin   //
// virtuaalityöpöydän Linuxissa: muissa järjestel- //
// missä toiminnalle ei anneta takuuta!            //
//*************************************************//

#include <iostream>
#include <fstream>
#include "merkkijonoapu.h"
#include "tiedostoluku.h"
#include "listat.h"
using namespace std;

int main() {
    cout << "Syota saantotiedoston nimi: " ;
    string tiedostonnimi{""} ;
    cin >> tiedostonnimi ;
    cin.ignore() ;

    Listat listat ;
    if(!hae_tiedot(tiedostonnimi,listat)) {
        return false ;
    }

    while(true ) {
        cout << "muunnospyynto> " ;
        string pyynto{""} ;
        getline(cin,pyynto) ;
        poista_valilyonnit_alusta_ja_lopusta(pyynto) ;
        double arvo{0} ;
        string kohdeyksikko{""} ;
        string lahtoyksikko{""} ;
        if(!paloittele_syote(pyynto,arvo,kohdeyksikko,lahtoyksikko)) {
            cerr << "Virhe kayttajan syotteessa: virheellinen syote"
                 << endl ;
            continue ;
        }
        double tulos = 0 ;
        if(listat.hae_muunnos(kohdeyksikko,lahtoyksikko,arvo,tulos)) {
            cout << tulos << endl ;
        }
        else {
            cerr << "Virhe kayttajan syotteessa: tuntematon muunnos"
                 << endl ;
            continue ;
        }
    }
}
