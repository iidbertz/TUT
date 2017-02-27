#include "palat.hh"
#include "tarkistus.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Funktio etsii vasemman ylakulman palan, kaantaa sen oikein pain ja palauttaa sen
Pala vasen_ylakulma(vector<Pala>& palat) {
    // Kaydaan palat-vektorin paloja lapi yksi kerrallaan
    for ( unsigned i = 0; palat.size() > i;  ++i) {
        string kuva; // Merkkijono, johon palan kuva tallennetaan
        kuva = palat.at(i).kuva(); // Tallennetaan palan kuva muuttujaan
        // Jos merkkijonon pituus on 10, se kuuluu vasempaan ylakulmaan
        if (kuva.size() == 10) {
            kuva.erase(9);
            int ylos{palat.at(i).reunanro(0)}; // Palan ylareuna
            int vasen{palat.at(i).reunanro(3)}; // Palan vasen reuna
            // Kierretaan palaa, kunnes se on oikein pain
            while (( ylos != 0 ) or ( vasen != 0 )) {
                palat.at(i).kierra();
                ylos = palat.at(i).reunanro(0);
                vasen = palat.at(i).reunanro(3);
            }
            palat.at(i).kaytetty(); // Merkitaan pala kaytetyksi
            return palat.at(i); // Palautetaan kaannetty pala
        }
    }
}

// Etsitaan riville seuraavaksi sopiva pala, kaannetaan se oikein pain ja palautetaan se
Pala seuraava_pala_rivilla(vector<Pala>& palat, Pala edellinen) {
    int ed_reuna = edellinen.reunanro(1); // Edellisen palan oikea reuna
    // Kaydaan palat-vektorin palat lapi yksi kerrallaan
    for ( unsigned i = 0; palat.size() > i;  ++i) {
        // Jos palaa ei ole kaytetty, tutkitaan sen ominaisuuksia
        if (palat.at(i).getKaytetty() == false) {
            // Kaydaan lapi palan laidat
            for ( int j = 0; j < 4 ; ++j ) {
                // Jos jokin laidoista tasmaa edellisen palan oikeaan laitaan, kierretaan pala oikein pain
                int reuna = palat.at(i).reunanro(j);
                if (ed_reuna == reuna) {
                    for (; j < 3; ++j){
                        palat.at(i).kierra();
                    }
                    palat.at(i).kaytetty(); // Merkitaan pala kaytetyksi
                    return palat.at(i); // Palautetaan kaannetty pala
                }
            }
        }
    }
}

// Etsitaan uuden rivin ensimmainen pala, kaannetaan se oikein pain ja palautetaan se
Pala uusi_rivi(vector<Pala>& palat, Pala ylempi) {
    int ylareuna = ylempi.reunanro(2); // Ylapuolisen palan alareuna
    // Kaydaan palat-vektorin palat lapi yksi kerrallaan
    for ( unsigned i = 0; palat.size() > i; ++i) {
        // Jos palaa ei ole viela kaytetty, tutkitaan sen ominaisuuksia
        if (palat.at(i).getKaytetty() == false) {
            // Kaydaan palan reunat lapi yksi kerrallaan
            for ( int j = 0; j < 4; ++j) {
                int reuna = palat.at(i).reunanro(j);
                // Jos jokin reuna tasmaa ylapuoliseen palaan, kaannetaan se oikein pain
                if (ylareuna == reuna) {
                    while (ylareuna != palat.at(i).reunanro(0)) {
                        palat.at(i).kierra();
                    }
                    palat.at(i).kaytetty(); // Merkitaan pala kaytetyksi
                    return palat.at(i); // Palautetaan kaannetty pala
                }
            }
        }
    }
}

// Tulostetaan palapeli
void tulostus(int leveys, vector<Pala> palapeli) {
    // Kaydaan palapelia lapi rivi kerrallaan
    for (unsigned korkeus = 0; korkeus < palapeli.size()/leveys; ++korkeus) {
        // Kaydaan paloja lapi rivi kerrallaan
        for ( int rivi = 1; rivi < 4; ++rivi ) {
            // Kaydaan lapi palan leveyden verran paloja
            for ( int i = 0; leveys > i;  ++i) {
                int indeksi = i+(korkeus*leveys);
                palapeli.at(indeksi).tulosta(rivi);
            }
        cout << endl;
        }
    }
}
