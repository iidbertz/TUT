#include "palat.hh"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Rakentajafunktio
Pala::Pala(const string& teksti):
    pala_{luo_pala(teksti)}, kaytetty_{false}{
}

// Luodaan uusi pala merkkijonosta
vector<string> Pala::luo_pala(const string& merkkijono) {
    vector<string> valmis_pala; // Vektoriin tallennetaan merkkijonosta luettu pala
    string kentan_sisalto{""}; // Merkkijono, joka lisataan vektoriin
    // Kaydaan lapi koko merkkijono
    for ( unsigned i = 0; merkkijono.length() > i;  ++i) {
        // Jos merkki ei ole :, lisataan se kentan_sisalto-merkkijonoon
        if ( merkkijono.at(i) != ':' ) {
            kentan_sisalto.push_back( merkkijono.at(i) );
        }
        // Jos merkkijonossa tulee vastaan :-merkki, lisataan sita edeltava osa vektoriin
        // Tyhjennetaan kentan_sisalto
        else {
            valmis_pala.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }
    }
    // Lisataan merkkijono on kayty kokonaan lapi, lisataan viimeinenkin osa siita vektoriin
    valmis_pala.push_back(kentan_sisalto);

    return valmis_pala; // Palautetaan valmis pala-vektori
}

// Muutetaan palan reuna int-muotoon
int Pala::reunanro(const int& sijainti) {
    string sisalto{""};
    int reuna{0};
    sisalto = pala_.at(sijainti);
    reuna = stoi(sisalto);
    return reuna;
}

// Muutetaan palan kuva string-muotoon
string Pala::kuva() {
    return pala_.at(4);
}

// Lasketaan, monta 0-reunaa palassa on
int Pala::laske_nollat() {
    int lkm{0};
    lkm = count(pala_.begin(), pala_.end(), "0");
    return lkm;
}

// Tulostaa palan
void Pala::tulosta(int rivi) const {
    if (rivi == 1) {
        cout << pala_.at(4).substr(0,3);
    }
    else if (rivi ==2) {
        cout << pala_.at(4).substr(3,3);
    }
    else if (rivi == 3) {
        cout << pala_.at(4).substr(6,3);
    }
}

// Kiertaa palaa 90 astetta myotapaivaan
void Pala::kierra(){
    // Kierretaan ensin palan laidat
    string eka_laita = pala_.at(0); // Tallennetaan 1. laita muuttujaan talteen
    pala_.at(0) = pala_.at(3);
    pala_.at(3) = pala_.at(2);
    pala_.at(2) = pala_.at(1);
    pala_.at(1) = eka_laita; // Sijoitetaan muuttujaan tallennettu laita viimeisena
    // Seuraavaksi kierretaan itse pala
    string vanha_pala = pala_.at(4);
    string uusi_pala{""};
    // Maaritellaan rotate-vektoriin palan merkkien uudet paikat
    vector<int> rotate{6,3,0,7,4,1,8,5,2};

    for (int i = 0; i < 9; ++i){
        int indeksi = rotate.at(i);

        // Maaritellaan merkkien -, |, / ja \ kaantaminen
        if (vanha_pala.at(indeksi) == '-'){
            vanha_pala.at(indeksi) = '|';
        }else if (vanha_pala.at(indeksi) == '|'){
            vanha_pala.at(indeksi) = '-';
        }else if (vanha_pala.at(indeksi) == '/'){
            vanha_pala.at(indeksi) = '\\';
        }else if(vanha_pala.at(indeksi) == '\\'){
            vanha_pala.at(indeksi) = '/';

        }uusi_pala.push_back(vanha_pala.at(indeksi));
    }pala_.at(4) = uusi_pala;
}

// Muutetaan tietoa siita, onko pala jo kaytetty palapelin rakentamisessa
void Pala::kaytetty() {
    kaytetty_ = true;
}

// Haetaan tieto siita, onko pala jo kaytetty
bool Pala::getKaytetty() const{
    return kaytetty_;
}
