// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Palautustehtävä T3
// 240482 ida.myller@student.tut.fi (10 h)
//
// Yksinkertainen päivyriohjelma, joka lukee tiedostoista kalenterimerkintöjä,
// pystyy tulostamaan kaikki tai yhden päivän tapahtumat, osaa poistaa ja lisätä
// yksittäisiä tapahtumia ja tallentaa kalenterin uuteen tiedostoon.

#include "kayttoliittyma.hh"
#include "tiedoston_luku.hh"
#include <string>

using namespace std;

int main() {
    string paivyritiedoston_nimi;
    cout << "Syota paivyritiedoston nimi: ";
    getline(cin, paivyritiedoston_nimi);

    Paivyri paivyri;

    if ( not lue_paivyritiedosto(paivyritiedoston_nimi, paivyri) ) {
        return 1;
    }

    // Ensimmäisen tiedoston lukemisen jälkeen ohjelman suoritus siirtyy
    // käyttöliittymään
    kayttoliittyma(paivyri);
}
