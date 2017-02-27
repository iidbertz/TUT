// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Palautustehtävä T5
// 240482 ida.myller@student.tut.fi (28.0 h)

// Ohjelma toimii yksikkömuuntimena, joka aloittaa lukemalla käyttäjän syöttämästä tiedostosta
// muunnoskaavat, joiden perusteella yksiköitä muunnetaan. Tämän jälkeen ohjelma pyytää käyttäjältä
// muunnospyynnön, jonka saatuaan muuntaa yksikön mikäli mahdollista ja tulostaa sen kolmen desimaalin
// tarkkuudella.

#include "tiedoston_luku.hh"
#include "muunnossaannot.hh"
#include "muunnoslasku.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <map>

using namespace std;

// Pyytää käyttäjältä muunnospyyntöjä ja vastaa niihin joko muunnetulla luvulla
// tai virheilmoituksella
void kayttoliittyma(map<string, Muunnokset> saannot) {
    string syoterivi;
    while ( true ) {
        cout << "muunnospyynto> ";
        getline(cin, syoterivi);

        if ( not cin or syoterivi == "" ) {
            break;
        }

        // Erotellaan käyttäjän syötteestä vaaditut tiedot
        string maara, lahto, kohde;
        if (tulkitse_syote(maara, lahto, kohde, syoterivi) == true) {
            // Tulostetaan virheilmoitus jos syötteessä oli liian vähän tietoja,
            // lähtö- ja kohdeyksiköt ovat samat tai jokin tiedoista on väärässä muodossa
            if ((maara.length() == 0) or (lahto.length() == 0) or (kohde.length() == 0)) {
                cout << "Virhe: syotteesta ei loydy tarvittavia tietoja!" << endl;
            }
            else if (lahto == kohde) {
                cout << "Virhe: lahto- ja kohdeyksikko ovat samat!" << endl;
            }
            else if ((tarkista_lukuarvo(maara) == false) or
                     (merkkien_tarkistus(lahto) == false) or
                     (merkkien_tarkistus(kohde) == false)) {
                cout << "Virhe: syote on vaarassa muodossa!" << endl;
            }

            // Muutetaan lukuarvo merkkijonosta reaaliluvuksi ja siirrytään laskemaan
            // muunnosta kutsumalla laske_muunnos-funktiota
            else {
                double arvo;
                arvo = stod(maara);

                laske_muunnos(arvo, lahto, kohde, saannot);
            }
        }
    }
}

// Luetaan käyttäjältä tiedosto, tallennetaan sen tiedot mikäli mahdollista ja kutsutaan
// käyttöliittymä-funktiota jatkamaan ohjelman suoritusta.
int main() {
    string syotetiedosto;
    map<string, Muunnokset> saannot; // alustetaan muuttuja, johon muunnoskaavat tallennetaan
    cout << "Syota saantotiedoston nimi: ";
    getline(cin, syotetiedosto);

    if ( not lue_tiedosto(syotetiedosto, saannot) ) {
        return 1;
    }

    kayttoliittyma(saannot);
}
