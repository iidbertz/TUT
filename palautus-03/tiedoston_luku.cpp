#include "tiedoston_luku.hh"

using namespace std;

// Lukee päivyritiedoston ja tulostaa tarvittaessa sopivat virheilmoitukset
bool lue_paivyritiedosto(const string& paivyritiedoston_nimi, Paivyri& paivyri) {
    ifstream tiedosto_olio{paivyritiedoston_nimi};
    if ( not tiedosto_olio ) {
        cout << "Virhe: paivyritiedostoa ei saanut avattua." << endl;
        return false;
    }

    string rivi;
    while ( getline(tiedosto_olio, rivi) ) {
        string::size_type erottimen_paikka;

        erottimen_paikka = rivi.find(':');

        if ( erottimen_paikka == string::npos ) {
            cout << "Virhe: syotetiedoston rivilta puuttui ':'." << endl;
            return false;
        }

        string paivays_str;
        string tapahtuman_kuvaus;

        paivays_str = rivi.substr(0, erottimen_paikka);
        tapahtuman_kuvaus = rivi.substr(erottimen_paikka + 1);

        if ( not paivyri.lisaa_tapahtuma(paivays_str, tapahtuman_kuvaus) ) {
            cout << "Virhe: tiedostossa virheellinen paivays." << endl;
            return false;
        }
    }

    tiedosto_olio.close();

    return true;
}

