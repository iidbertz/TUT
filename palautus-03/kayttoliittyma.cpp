#include "tiedoston_luku.hh"
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;


namespace {

    // Tulostaa päivyrin kaikki tapahtumat
    void tulosta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        loppurivi >> ws;

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: tulosta-komennon perassa ylimaaraista." << endl;
            return;
        }
        else {
            paiv.tulosta();
        }
    }

    // Näyttää päivyrin tapahtumat yhdeltä päivältä
    void nayta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara ei saa olla tyhja." << endl;
            return;
        }

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: nayta-komennon perassa ylimaaraista." << endl;
            return;
        }

        paiv.nayta(paivamaara);
    }

    // Lisää päivämäärälle tapahtuman
    void lisaa_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;
        string tapahtuma;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara puuttui." << endl;
            return;
        }

        getline(loppurivi, tapahtuma);
        if ( tapahtuma == "" ) {
            cout << "Virhe: tapahtuma ei saa olla tyhja." << endl;
            return;
        }

        paiv.lisaa_tapahtuma(paivamaara, tapahtuma);
    }

    // Poistaa päivämäärältä sille ensin lisätyn tapahtuman
    void poista_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara ei saa olla tyhja." << endl;
            return;
        }

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: poista-komennon perassa ylimaaraista." << endl;
            return;
        }

        paiv.poista(paivamaara);
    }

    // Lukee uuden tiedoston ja lisää tapahtumat kalenteriin
    void lue_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string tiedoston_nimi;

        loppurivi >> ws;
        getline(loppurivi, tiedoston_nimi);

        if ( tiedoston_nimi.empty() ) {
            cout << "Virhe: tiedoston nimi ei saa olla tyhja." << endl;
            return;
        }

        lue_paivyritiedosto(tiedoston_nimi, paiv);
    }

    // Tallettaa kalenterin uuteen tiedostoon, joka on samassa muodossa
    // kuin ohjelman lukemat päivyritiedostot
    void talleta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string tiedoston_nimi;

        loppurivi >> ws;
        getline(loppurivi, tiedoston_nimi);

        if ( tiedoston_nimi.empty() ) {
            cout << "Virhe: tiedoston nimi ei saa olla tyhja." << endl;
            return;
        }

        paiv.talleta(tiedoston_nimi);
    }

}

// Käyttöliittymä pyytää käyttäjältä komennon ja kutsuu sopivaa funktiota
// komennon perusteella
void kayttoliittyma(Paivyri& paivyri) {
    string syoterivi;
    while ( true ) {
        cout << "paivyrikomento> ";
        getline(cin, syoterivi);

        if ( not cin or syoterivi == "" ) {
            break;
        }

        istringstream rivivirta{syoterivi};

        string komento;
        rivivirta >> komento;

        if ( not rivivirta ) {
            cout << "Virhe: komennoksi ei saa syottaa pelkkia valeja." << endl;
            continue;
        }

        if ( komento == "tulosta" ) {
            tulosta_toiminto(paivyri, rivivirta);

        } else if ( komento == "nayta" ) {
            nayta_toiminto(paivyri, rivivirta);

        } else if ( komento == "lisaa" ) {
            lisaa_toiminto(paivyri, rivivirta);

        } else if ( komento == "poista" ) {
            poista_toiminto(paivyri, rivivirta);

        } else if ( komento == "lue" ) {
            lue_toiminto(paivyri, rivivirta);

        } else if ( komento == "talleta" ) {
            talleta_toiminto(paivyri, rivivirta);

        } else {
            cout << "Virhe: tuntematon komento." << endl;
        }
    }
}
