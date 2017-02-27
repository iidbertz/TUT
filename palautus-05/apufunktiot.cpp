// Moduuli: apufunktiot / tiedosto: apufunktiot.cpp
// Moduulin apufunktiot toteutustiedosto:
// sisältää alustavat funktiot, joiden sijoittaminen
// muihin moduuleihin ei tuntunut järkevältä.

#include "apufunktiot.hh"

using namespace std;

// Funktio poistaa kaikki välilyönnit merkkijonosta
// ja palautaa välilyönnittömän merkkijonon
string poista_valit(string rivi) {
    string rivi2;
    for (unsigned i = 0; i < rivi.length(); ++i) {
        if (rivi.at(i) != ' ') {
            rivi2 += rivi.at(i);
        }
    }
    return rivi2;
}

bool tulkitse_kaava(string rivi, string& lahtoyksikko, string& kohdeyksikko,
                    string& kerroin, string& vakio) {
    auto erotin{rivi.find("<=")}, kertomerkki{rivi.find('*')},
            plus{rivi.find('+')}, miinus{rivi.find('-')};

    // Tarkistetaan, että nuoli ja kertomerkki löytyvät
    // Tulostetaan virheilmoitus jos eivät
    if ((erotin == string::npos) or (kertomerkki == string::npos)) {
        cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
        return false;
    }

    kohdeyksikko = rivi.substr(0, erotin);
    kerroin = rivi.substr(erotin+2, kertomerkki-erotin-2);

    // Jos riviltä löytyy +-merkki
    if (plus != string::npos) {
        if ((erotin > kertomerkki) or (kertomerkki > plus)) {
            cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
            return false;
        }
        vakio = rivi.substr(plus+1);
        lahtoyksikko = rivi.substr(kertomerkki+1, plus-kertomerkki-1);
        return true;
    }

    // Jos riviltä löytyy miinus-merkki
    else if (miinus != string::npos) {
        if ((erotin > kertomerkki) or (kertomerkki > miinus)) {
            cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
            return false;
        }
        vakio = ('-' + rivi.substr(miinus+1));
        lahtoyksikko = rivi.substr(kertomerkki+1, miinus-kertomerkki-1);
        return true;
    }

    // Jos riviltä ei löydy kumpaakaan
    else {
        if (erotin > kertomerkki) {
            cout << "Virhe: tiedostossa virheellinen rivi!" << endl;
            return false;
        }
        lahtoyksikko = rivi.substr(kertomerkki+1);
        return true;
    }
}

// Tarkistaa, ettei yksikköjen nimissä ole kiellettyjä merkkejä
// ja että /-merkki ei ole ensimmäinen eikä viimeinen merkki
bool merkkien_tarkistus(string yksikko) {
    string sallitut_merkit{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWX"
                           "YZ/"};
    for (char& c: yksikko){
        if (sallitut_merkit.find(c) == string::npos) {
            return false;
        }
        else {
            if ( c == '/' ) {
                if ( (yksikko.find(c) == 0) or (yksikko.find(c) == yksikko.length()-1))
                    return false;
            }
        }
    }
    return true;
}

// Tallettaa muunnoskaavan saannot-mappiin
bool talleta_rivi(string lahtoyksikko, string kohdeyksikko, double kerroin, double vakio,
                  map<string, Muunnokset> &saannot) {
    vector<double> luvut; // Vektori, johon tallennetaan kerroin ja mahdollinen vakio
    luvut.push_back(kerroin);
    if (vakio != 0.0) {
        luvut.push_back(vakio);
    }

    Muunnokset muunnos(lahtoyksikko, luvut);

    // Käydään iteraattorin avulla läpi saannot-map ja etsitään,
    // onko sama kohdeyksikkö tallennettu jo aiemmin
    map<string, Muunnokset>::iterator iter;
    iter = saannot.begin();

    while (iter != saannot.end()) {
        // Jos kohdeyksikkö löytyy, tutkitaan onko vastaava muunnos jo tallennettu
        // ja jos ei, lisätään kaava sen hyötytieto-luokkaan
        if (iter->first == kohdeyksikko) {
            if (iter->second.etsi_luvut(lahtoyksikko) == true) {
                cout << "Virhe: Paallekkaisia laskukaavoja!" << endl;
                return false;
            }
            iter->second.lisaa_muunnos(lahtoyksikko, luvut);
            return true;
        }
        // Jos lähtöyksikkö löytyy, tutkitaan onko vastaava muunnos jo tallennettu
        else if (iter->first == lahtoyksikko) {
            if (etsi_kaava(lahtoyksikko, kohdeyksikko, saannot) == true) {
                cout << "Virhe: Paallekkaisia laskukaavoja!" << endl;
                return false;
            }
        }
        ++iter;
    }

    // Jos kohdeyksikköä ei löydy, luodaan uusi hakuavain-hyötytieto -pari
    saannot.insert({kohdeyksikko, muunnos});
    return true;
}

// Funktio tarkistaa, löytyykö yksikköpari saannot-mapista käänteisessä järjestyksessä
bool etsi_kaava(string lahtoyksikko, string kohdeyksikko, map<string, Muunnokset> saannot) {
    map<string, Muunnokset>::iterator iter;
    iter = saannot.begin();

    while (iter != saannot.end()) {
        if (iter->first == lahtoyksikko) {
            if (iter->second.etsi_luvut(kohdeyksikko) == true) {
                return true;
            }
        }
        ++iter;
    }
    return false;
}

// Funktio erittelee käyttäjän antamasta muunnospyynnöstä
// sekä luvun että lähtö- ja kohdeyksikön
bool tulkitse_syote(string &maara, string &lahto, string &kohde, string syoterivi) {
    string merkkijono; // Apumuuttuja erittelyn helpottamiseksi
    // Käydään syötteen merkit läpi yksi kerrallaan
    for (unsigned i = 0; i < syoterivi.length(); ++i) {
        // Jos kyseessä ei ole välilyönti
        if (syoterivi.at(i) != ' ') {
            if (kohde.length() != 0) {
                cout << "Virhe: syotteessa on liikaa tietoja!" << endl;
                return false;
            }
            merkkijono += syoterivi.at(i); // Lisätään merkki apumuuttujaan
        }
        else {
            // Jos kyseessä on välilyönti ja apumuuttuja ei ole tyhjä
            if (merkkijono.length() != 0) {
                // Tallennetaan ensin lukuarvo
                if (maara.length() == 0) {
                    maara = merkkijono;
                    merkkijono.erase(); // Tyhjennetään apumuuttuja
                }
                // Tallennetaan lähtöyksikkö
                else if (lahto.length() == 0) {
                    lahto = merkkijono;
                    merkkijono.erase();
                }
                // Tallennetaan kohdeyksikkö
                else if (kohde.length() == 0) {
                    kohde = merkkijono;
                    merkkijono.erase();
                }

            }
        }
    }
    // Jos syöte ei lopu välilyöntiin, tallennetaan lopuksi merkkijonon
    // sisältö kohdeyksiköksi
    if (kohde.length() == 0) {
        kohde = merkkijono;
    }
    return true;
}

// Funktio tarkistaa, että merkkijono voidaan muuttaa reaaliluvuksi
bool tarkista_lukuarvo(string maara){
    string sallitut_merkit{"0123456789.-"};
    for (char& c: maara){
        if (sallitut_merkit.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

// Funktio etsii halutun kohdeyksikön saannot-mapista ja palauttaa totuusarvon
bool etsi_yksikko(string kohde, map<string, Muunnokset> saannot) {
    map<string, Muunnokset>::iterator iter;
    iter = saannot.begin();

    while (iter != saannot.end()) {
        if (iter->first == kohde) {
            return true;
        }
        ++iter;
    }
    return false;
}
