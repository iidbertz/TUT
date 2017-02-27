#include "paivyri.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


// Lisää tapahtumia kalenteriin
bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {
    Paivays paiv;
    if (!paiv.aseta(paivamaara)) {
        cout << "Virhe: Virheellinen paivamaara!" << endl;
        return false;
    }
    // Jos päivällä on jo tapahtumia, lisätään uusi tapahtuma viimeiseksi
    if (paivyridata_.find(paiv) != paivyridata_.end()) {
        paivyridata_.at(paiv).push_back(kuvaus);
    }
    // Jos päivällä ei ole tapahtumia, lisätään päivä ja tapahtuma kalenteriin
    else {
        vector<string> tapahtuma;
        tapahtuma.push_back(kuvaus);
        paivyridata_.insert({paiv, tapahtuma});
    }

    return true;
}

// Tulostaa kaikki kalenterin tapahtumat
void Paivyri::tulosta() {
    map<Paivays, vector<string>>::iterator iter;
    iter = paivyridata_.begin();
    if  (iter == paivyridata_.end()) {
        cout << "Virhe: Paivyri on tyhja." << endl;
    }
    // Käydään kaikki kalenterin päivät läpi ja tulostetaan ne
    while (iter != paivyridata_.end()) {
        vector<string>::iterator iterpvm = (iter->second).begin();
        iter->first.tulosta();
        // Käydään päivältä kaikki tapahtumat läpi ja tulostetaan ne
        while (iterpvm != (iter->second).end()) {
            cout << "    " << *iterpvm << endl;
            ++iterpvm;
        }
        ++iter;
    }
}

// Näyttää kalenterin tapahtumat yhdeltä päivältä
void Paivyri::nayta(const string& pvm) {
    Paivays paiv;
    if (!paiv.aseta(pvm)) {
        cout << "Virhe: Virheellinen paivamaara!" << endl;
        return;
    }
    if (paivyridata_.find(pvm) != paivyridata_.end()) {
        paiv.tulosta(); // Tulostaa päivämäärän
        unsigned i {0};
        // Tulostetaan kaikki päivämäärälle lisätyt tapahtumat
        while (i < paivyridata_.at(paiv).size()) {
            cout << "    " << paivyridata_.at(paiv).at(i) << endl;
            ++i;
        }
    }
    else {
        cout << "Paivamaaralle ei ole tehty merkintoja." << endl;
    }
}

// Poistetaan tietyn päivämäärän vanhin tapahtuma
void Paivyri::poista(const string& pvm) {
    Paivays paiv;
    if (!paiv.aseta(pvm)) {
        cout << "Virhe: Virheellinen paivamaara!" << endl;
        return;
    }
    if (paivyridata_.find(paiv) != paivyridata_.end()) {
        paivyridata_.at(paiv).erase(paivyridata_.at(paiv).begin());

        // Jos poistettu tapahtuma oli päivän ainoa, poistetaan myös päivämäärä
        if (paivyridata_.at(paiv).size() == 0) {
            paivyridata_.erase(paiv);
        }
    }
    else {
        cout << "Paivamaarana ei ole poistettavaa merkintaa." << endl;
    }
}

// Talletetaan kalenteri uuteen tiedostoon sopivassa muodossa
void Paivyri::talleta(const string &tiedostonimi) {
    map<Paivays, vector<string>>::iterator iter;
    iter = paivyridata_.begin();
    ofstream tiedosto;
    tiedosto.open(tiedostonimi);

    while (iter != paivyridata_.end()) {
        vector<string>::iterator iterpvm = (iter->second).begin();
        while (iterpvm != (iter->second.end())) {
            tiedosto << iter->first.merkkijonoksi() << ":" << *iterpvm << endl;
            ++iterpvm;
        }
        ++iter;
    }
    tiedosto.close();
}
