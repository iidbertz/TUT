// Moduuli: muunnoslasku / tiedosto: muunnoslasku.cpp
// Moduulin muunnoslasku toteutustiedosto:
// sisältää yksikkömuunnosten laskemista käsittelevät funktiot.

#include "muunnoslasku.hh"

// Funktio laskee käyttäjän pyytämän yksikkömuunnoksen
void laske_muunnos(double arvo, string lahto, string kohde,
                   map<string, Muunnokset> saannot) {
    double tulos;
    // Jos haluttu kohdeyksikkö löytyy saannot-mapin kohdeyksiköistä
    if (etsi_yksikko(kohde, saannot) == true) {
        // Jos kohdeyksikön kohdalta löytyy haluttu muunnos, lasketaan se
        if (laske_suoraan(arvo, lahto, kohde, saannot, tulos) != false) {
            cout << setprecision(3) << fixed << tulos << endl;
            return;
        }
        // Jos haluttua muunnosta ei löydy, etsitään lähtöyksikköä
        else if (etsi_yksikko(lahto, saannot) == true) {
            // Jos lähdeyksikkö löytyy, etsitään sen kohdalta kohdeyksikköä
            // ja lasketaan tulos kääntäen kaava toiseen suuntaan
            if (laske_kaantaen(arvo, lahto, kohde, saannot, tulos) == true) {
                cout << setprecision(3) << fixed << tulos << endl;
                return;
            }
        }
        // Jos haluttua muunnosta ei löydy, tulostetaan virheilmoitus
        else {
            cout << "Virhe: tuntematon muunnos!" << endl;
            return;
        }
    }

    // Jos kohdeyksikköä ei löytynyt, etsitään lähtöyksikköä
    else if (etsi_yksikko(lahto, saannot) == true) {
        // Jos lähtöyksikkö löytyy, etsitään sen kohdalta haluttu kohdeyksikkö
        // ja lasketaan tulos kääntäen kaava toiseen suuntaan
        if (laske_kaantaen(arvo, lahto, kohde, saannot, tulos) == true) {
            cout << setprecision(3) << fixed << tulos << endl;
            return;
        }
        // Jos kohdeyksikköä ei löydy, tulostetaan virheilmoitus
        else {
            cout << "Virhe: tuntematon muunnos!" << endl;
            return;
        }
    }

    // Jos kumpaakaan yksikköä ei löydy saannot-mapin hakuavaimista,
    // tulostetaan virheilmoitus
    cout << "Virhe: tuntematon muunnos!" << endl;
    return;
}

// Lasketaan tulos tapauksessa, jossa kaava löytyy suoraan saannot-mapista
bool laske_suoraan(double arvo, string lahto, string kohde,
                   map<string, Muunnokset> saannot, double& tulos) {

    // Käydään saannot-map läpi iteraattorin avulla, kunnes löydetään
    // kohdeyksikön sijainti
    map<string, Muunnokset>::iterator iter;
    iter = saannot.begin();

    while (iter->first != kohde) {
        ++iter;
    }

    // Jos kohdeyksikön kohdalta ei löydy haluttua lähtöyksikköä,
    // palautetaan arvo false
    if (iter->second.etsi_luvut(lahto) == false) {
        return false;
    }

    else {
        // Alustetaan luvut-vektori kaavaa vastaavilla lukuarvoilla
        vector<double> luvut{(iter->second.hae_luvut(lahto))};

        // Jos kaavassa ei ole vakiota
        if (luvut.size() == 1) {
            tulos = arvo*luvut.at(0);
        }

        // Jos kaavassa on vakio
        else if (luvut.size() == 2) {
            tulos = arvo*luvut.at(0)+luvut.at(1);
        }

        return true;
    }
}

// Lasketaan muunnos tapauksessa, jossa kaava on ensin käännettävä päin vastoin
bool laske_kaantaen(double arvo, string lahto, string kohde, map<string, Muunnokset> saannot, double& tulos) {
    // Käydään saannot-map läpi iteraattorin avulla, kunnes löydetään
    // lähtöyksikön sijainti
    map<string, Muunnokset>::iterator iter;
    iter = saannot.begin();

    while (iter->first != lahto) {
        ++iter;
    }

    // Jos lähtöyksikön kohdalta ei löydy haluttua kohdeyksikköä,
    // palautetaan arvo false
    if (iter->second.etsi_luvut(kohde) == false) {
        return false;
    }

    else {
        // Alustetaan luvut-vektori kaavaa vastaavilla lukuarvoilla
        vector<double> luvut{(iter->second.hae_luvut(kohde))};

        // Jos kaavassa ei ole vakiota
        if (luvut.size() == 1) {
            tulos = arvo/luvut.at(0);
        }

        // Jos kaavassa on vakio
        else if (luvut.size() == 2) {
            tulos = (arvo-luvut.at(1))/luvut.at(0);
        }

        return true;
    }
}

