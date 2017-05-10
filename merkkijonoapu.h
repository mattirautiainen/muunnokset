#ifndef MERKKIJONOAPU_H
#define MERKKIJONOAPU_H

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string poista_valilyonnit(string& mjono) ;
string poista_valilyonnit_alusta_ja_lopusta(string& mjono) ;
bool paloittele_rivi(const string& mjono,
                     const vector<string>& erottimet,
                     vector<string>& kentat) ;
double muuta_string_doubleksi(const string& mjono) ;
bool onko_double_string(const string& mjono) ;
bool paloittele_syote(string syote, double &arvo, string &kohdeyksikko,
                      string &lahtoyksikko) ;

#endif // MERKKIJONOAPU_H
