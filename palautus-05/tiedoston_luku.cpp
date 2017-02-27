// Moduuli: tiedoston luku / tiedosto: tiedoston_luku.cpp
// Moduulin tiedoston luku toteutustiedosto:
// sisältää tiedoston lukemiseen käytettävän funktion.

#include "tiedoston_luku.hh"
#include "apufunktiot.hh"
#include <fstream>
#include <iostream>

using namespace std;

// Lukee sääntötiedoston ja tulostaa tarvittaessa sopivat virheilmoitukset
bool lue_tiedosto(const string& syotetiedosto, map<string, Muunnokset>& saannot) {
    ifstream tiedosto_olio{syotetiedosto};
    if ( not tiedosto_olio ) {
        cout << "Virhe: saantotiedostoa ei saatu avattua." << endl;
        return false;
    }

    string rivi;

    // Käydään tiedosto läpi rivi riviltä
    while ( getline(tiedosto_olio, rivi) ) {

        rivi = poista_valit(rivi);

        // Käsitellään rivit, jotka eivät ole tyhjiä ja jotka eivät ole kommentteja
        if ((rivi.length() != 0) and (rivi.at(0) != '#')) {
            string lahtoyksikko, kohdeyksikko, kerroin_str, vakio_str;
            if (tulkitse_kaava(rivi, lahtoyksikko, kohdeyksikko, kerroin_str, vakio_str) == true) {
                // Tarkistetaan, että kaavat ovat oikeassa muodossa
                if ((merkkien_tarkistus(lahtoyksikko) == false) or
                        (merkkien_tarkistus(kohdeyksikko) == false) or
                        (tarkista_lukuarvo(kerroin_str) == false)){
                    cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
                    return false;
                }

                double kerroin, vakio{0.0};
                kerroin = stod(kerroin_str);
                if (vakio_str.length() != 0) {
                    if (tarkista_lukuarvo(vakio_str) == false) {
                        cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
                        return false;
                    }
                    vakio = stod(vakio_str);
                }
                if (talleta_rivi(lahtoyksikko, kohdeyksikko, kerroin, vakio, saannot) == false) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }

    tiedosto_olio.close();
    return true;
}
