#include "paivyri.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Tapahtumat-luokkaan tallennetaan päivyrin tapahtumat
Tapahtumat::Tapahtumat(): ekaOsoit_{nullptr}, vikaOsoit_{nullptr}{
}

// Tulostaa tapahtumien kuvaukset
void Tapahtumat::tulosta() const{
    shared_ptr<Tapahtuma>
            tulOsoit{ekaOsoit_};

    while (tulOsoit != nullptr) {
        cout << "    " << tulOsoit->tapahtuma_ << endl;
        tulOsoit = tulOsoit->seurOsoit;
    }
}

// Lisää tapahtuman
bool Tapahtumat::lisaa_tapahtuma(const string& syote) {
    shared_ptr<Tapahtuma> uusiOsoit{
        new Tapahtuma{syote, nullptr}};

    if (ekaOsoit_ == nullptr) {
        ekaOsoit_ = vikaOsoit_ = uusiOsoit;
        uusiOsoit->seurOsoit = nullptr;
    }

    else {
        vikaOsoit_->seurOsoit = uusiOsoit;
        vikaOsoit_ = uusiOsoit;
        uusiOsoit->seurOsoit = nullptr;
    }
    return true;
}

// Poistaa tapahtuman
bool Tapahtumat::poista() {
    ekaOsoit_ = ekaOsoit_->seurOsoit;
    return true;
}

// Tallettaa tapahtumat tiedostoon
bool Tapahtumat::talleta(const string& paivam, ofstream& tiedosto) {
    shared_ptr<Tapahtuma> tallennusOsoit{ekaOsoit_};
    while (tallennusOsoit != nullptr) {
        tiedosto << paivam << tallennusOsoit->tapahtuma_ << endl;
        tallennusOsoit = tallennusOsoit->seurOsoit;
    }

    return true;
}

// Luokkaan tallennetaan päivyri
Paivyri::Paivyri(): ekaOsoit_{nullptr}, vikaOsoit_{nullptr} {
}

// Lisää tapahtumia kalenteriin
bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {
    Paivays paiv;
    if (!paiv.aseta(paivamaara)) {
        cout << "Virhe: Virheellinen paivamaara!" << endl;
        return false;
    }
    shared_ptr<Paiva> uusiOsoit { new Paiva{paiv, nullptr, {}, 0}};

    if (ekaOsoit_ == nullptr) {
        ekaOsoit_ = vikaOsoit_ = uusiOsoit;
        uusiOsoit->seurOsoit = nullptr;
    }

    else if (uusiOsoit->paiv < ekaOsoit_->paiv) {
        uusiOsoit->seurOsoit = ekaOsoit_;
        ekaOsoit_ = uusiOsoit;
    }

    else if (uusiOsoit->paiv > vikaOsoit_->paiv) {
        vikaOsoit_->seurOsoit = uusiOsoit;
        uusiOsoit->seurOsoit = nullptr;
        vikaOsoit_ = uusiOsoit;
    }

    else {
        shared_ptr<Paiva> edellOsoit{ekaOsoit_};

        while (edellOsoit->seurOsoit->paiv < uusiOsoit->paiv){
            edellOsoit = edellOsoit->seurOsoit;
        }
        if (edellOsoit->paiv == uusiOsoit->paiv){
            uusiOsoit = edellOsoit;
        }
        else if (edellOsoit->seurOsoit->paiv == uusiOsoit->paiv) {
            uusiOsoit = edellOsoit->seurOsoit;
        }

        else {
            uusiOsoit->seurOsoit = edellOsoit->seurOsoit;
            edellOsoit->seurOsoit = uusiOsoit;
        }
    }
    uusiOsoit->tapahtuma.lisaa_tapahtuma(kuvaus); // Tapahtuman kuvaukset käsitellään tapahtuma-luokassa
    uusiOsoit->koko_ += 1;
    return true;
}

// Tulostaa kaikki kalenterin tapahtumat
void Paivyri::tulosta() const{
    shared_ptr<Paiva> tulOsoit {ekaOsoit_};

    if (tulOsoit == nullptr) {
        cout << "Virhe: Paivyri on tyhja." << endl;
        return;
    }

    // Käydään läpi kaikki päivämäärät
    while (tulOsoit != nullptr) {
        tulOsoit->paiv.tulosta(); // Tulostetaan päivämäärä
        tulOsoit->tapahtuma.tulosta(); // Tulostetaan tapahtumat
        tulOsoit = tulOsoit->seurOsoit; // Siirrytään seuraavaan kohtaan
    }
}

// Näyttää kalenterin tapahtumat yhdeltä päivältä
bool Paivyri::nayta(const string& pvm) {
    shared_ptr<Paiva> tulOsoit{ekaOsoit_};

    // Käydään läpi kaikki päivät
    while (tulOsoit != nullptr) {
        // Jos kohdan päivämäärä täsmää haluttuun päivämäärään
        if (tulOsoit->paiv == pvm) {
            tulOsoit->paiv.tulosta(); // Tulostaa päivämäärän
            tulOsoit->tapahtuma.tulosta(); // Tulostaa tapahtumat
            return true;
        }

        // Jos kohdan päivämäärä ei täsmää, siirrytään seuraavaan kohtaan
        else {
            tulOsoit = tulOsoit->seurOsoit;
        }
    }

    // Tulostetaan ilmoitus jos päivämäärää ei löydy
    cout << "Paivamaaralle ei ole tehty merkintoja." << endl;
    return false;
}

// Poistetaan tietyn päivämäärän vanhin tapahtuma
bool Paivyri::poista(const string& pvm) {
    shared_ptr<Paiva> poistoOsoit{ekaOsoit_};

    if (ekaOsoit_ == nullptr){
        cout << "Virhe: Paivyri on tyhja." << endl;
        return false;
    }

    // Käydään kaikki päivät läpi
    while (poistoOsoit != nullptr) {
        // Lopetetaan silmukka jos päivä täsmää
        if (poistoOsoit->paiv == pvm) {
            break;
        }

        // Jos poistettavia merkintöjä ei ole, tulostetaan ilmoitus
        else if (poistoOsoit->seurOsoit == nullptr) {
            cout << "Paivamaarana ei ole poistettavaa merkintaa." << endl;
            return false;
        }

        // Muussa tapauksessa siirrytään seuraavaan kohtaan
        else {
            poistoOsoit = poistoOsoit->seurOsoit;
        }
    }

    // Poistetaan tapahtuma, jos poistettavaa löytyi
    if (poistoOsoit->koko_ > 1) {
        poistoOsoit->tapahtuma.poista();
        poistoOsoit->koko_ -= 1;
        return true;
    }

    shared_ptr<Paiva> edellOsoit{ekaOsoit_};

    if (edellOsoit->paiv != poistoOsoit->paiv) {
        while (edellOsoit->seurOsoit->paiv != poistoOsoit->paiv) {
            edellOsoit = edellOsoit->seurOsoit;
        }

        if (poistoOsoit->seurOsoit == nullptr) {
            edellOsoit->seurOsoit = nullptr;
        }

        else {
            edellOsoit->seurOsoit = poistoOsoit->seurOsoit;
        }
    }

    else {
        ekaOsoit_ = ekaOsoit_->seurOsoit;
    }
    return true;
}

// Talletetaan kalenteri uuteen tiedostoon sopivassa muodossa
bool Paivyri::talleta(const string &tiedostonimi) {
    shared_ptr<Paiva> paivaOsoit{ekaOsoit_};

    ofstream tiedosto;
    tiedosto.open(tiedostonimi);

    // Käydään kaikki päivämäärät läpi
    while (paivaOsoit != nullptr) {
        string paivam;
        paivam = paivaOsoit->paiv.merkkijonoksi() + ":"; // Tallennetaan päivä merkkijonoksi
        paivaOsoit->tapahtuma.talleta(paivam, tiedosto); // Kutsutaan talleta-funktiota tapahtuma-luokassa
        paivaOsoit = paivaOsoit->seurOsoit; // Siirrytään seuraavaan kohtaan
    }

    tiedosto.close();
    return true;
}

