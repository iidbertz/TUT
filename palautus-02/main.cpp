// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Palautustehtävä T2
// 240482 ida.myller@student.tut.fi (27 h)

#include "palat.hh"
#include "tarkistus.hh"
#include "kokoaminen.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // Pyydetaan kayttajalta tiedosto, jossa on koottavan palapelin palat
    string tiedoston_nimi{""};
    cout << "Luettava tiedosto: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto{tiedoston_nimi};
    // Jos tiedostoa ei voida avata, tulostetaan virheilmoitus
    if ( not tiedosto ) {
        cout << "Virhe tiedoston avaamisessa." << endl;
    }
    else {
        string rivi; // rivi tiedostossa
        vector<Pala> palat; // vektori, johon palat tallennetaan tiedostosta
        vector<int> reunat; // vektori, johon tallennetaan palojen reunoja myohempaa tarkastelua varten
        while ( getline(tiedosto, rivi) ) {
            Pala pala{rivi};

            // Tallennetaan palan laidat int-muotoon ja kuva string-muotoon tarkistusta varten.
            // Lisataan kaikki muut laidat paitsi reunimmaiset (=0) reunat-vektoriin.
            int ylos = pala.reunanro(0);
                if (ylos != 0) {
                    reunat.push_back(ylos);
                }
            int oikea = pala.reunanro(1);
                if (oikea != 0) {
                    reunat.push_back(oikea);
                }
            int alas = pala.reunanro(2);
                if (alas != 0) {
                    reunat.push_back(alas);
                }
            int vasen = pala.reunanro(3);
                if (vasen != 0) {
                    reunat.push_back(vasen);
                }
            // Tallennetaan palan myohemmin tulostettava osa merkkijonoksi
            string kuva = pala.kuva();

            // Tarkistetaan, etta kaikki reunat ovat positiivisia kokonaislukuja
            if (neg_reuna(ylos, oikea, alas, vasen) == false) {
                cout << "Virhe: palan reunat eivat ole positiivisia kokonaislukuja." << endl;
            }
            // Tarkistetaan, että kuvassa on vain sallittuja merkkeja
            else if (merkit(kuva) == false) {
                cout << "Virhe: palassa on virheellisia merkkeja." << endl;
            }
            // Tarkistetaan, etta kuva on oikean kokoinen
            else if (kuvan_koko(kuva) == false) {
                cout << "Virhe: pala on vaaran kokoinen." << endl;
            }
            // Tarkistetaan että 0-reunoja on sallittu maara per pala ja ne eivat ole
            // vastakkain
            else if (nollat(pala, ylos, oikea, alas, vasen) == false) {
                cout << "Virhe: palassa on liikaa 0-reunoja tai ne ovat vastakkain." << endl;
            }
            // Jos ongelmia ei ilmennyt, tallennetaan pala palat-vektoriin
            else {
                palat.push_back(pala);
            }
        }
        int ylakulma{0}; // muuttujaan tallennetaan ylakulmaksi tarkoitettujen palojen lukumaara virhetarkistusta varten
        unsigned nollat{0}; // muuttujaan tallennetaan 0-laitojen lukumaara virhetarkistusta varten
        // Ylakulma: lasketaan ylakulmaksi tarkoitettujen palojen maara
        // Nollat: lasketaan palojen 0-reunojen maara
        for (unsigned i=0; i < palat.size(); ++i) {
            ylakulma = ylakulma_tarkistus(palat.at(i), ylakulma);
            nollat = nollien_maara(palat.at(i), nollat);
        }
        // Jos ylakulmapaloja ei ole tasan 1, tulostetaan virhe
        if (ylakulma != 1) {
            cout << "Virhe: vasempaan ylakulmaan tarkoitettuja paloja voi olla vain 1." << endl;
        }
        // Jos jokaista reunaa (!=0) ei ole tasan 2, tulostetaan virhe
        else if (sisareunojen_tarkistus(reunat) == false) {
            cout << "Virhe: palojen reunat eivat tasmaa." << endl;
        }
        else {
            // Aloitetaan palapelin kokoaminen.
            vector<Pala> palapeli; // Vektori, johon tallennetaan palapelin palat oikeassa jarjestyksessa
            palapeli.push_back(vasen_ylakulma(palat)); // Aloitetaan vasemman ylakulman palasta
            int leveys{0}; // Muuttuja, johon tallennetaan palapelin leveys
            bool leveys_tiedossa = false; // Tieto siita, onko palan leveys jo tallennettu
            // Kaydaan palat-vektorin paloja lapi, kunnes kaikki on lisatty palapeli-vektoriin
            while ( palat.size() != palapeli.size() ) {
                // Lisataan rivin seuraava pala, kunnes saavutetaan palapelin oikea reuna
                palapeli.push_back(seuraava_pala_rivilla(palat, palapeli.at(palapeli.size()-1)));
                // Kun palapelin oikea reuna saavutetaan, vaihdetaan rivia
                if ((palapeli.at(palapeli.size()-1).reunanro(1) == 0) and (palat.size() != palapeli.size())) {
                    // Tallennetaan palapelin leveys, ellei sita ole viela tallennettu
                    if (leveys_tiedossa == false) {
                        leveys = palapeli.size();
                        leveys_tiedossa = true;
                    }
                    // Etsitaan uuden rivin ensimmainen pala
                    palapeli.push_back(uusi_rivi(palat, palapeli.at(palapeli.size()-leveys)));
                }

            }
            // Tarkistetaan, onko palojen 0-reunoja oikea maara
            if (nollat != 2*(leveys + palapeli.size()/leveys)) {
                cout << "Virhe: vaara maara 0-reunoja." << endl;
            }
            // Jos kaikki on sujunut ongelmitta, tulostetaan valmis palapeli
            else {
                tulostus(leveys, palapeli);
            }
        }
        }
}

