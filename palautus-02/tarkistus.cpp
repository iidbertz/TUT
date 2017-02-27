#include "palat.hh"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Tarkistetaan, etta palan reunat ovat positiivisia kokonaislukuja
// Palautetaan true tai false
bool neg_reuna(int ylos, int oikea, int alas, int vasen) {
    if ((ylos < 0) or (oikea < 0) or (alas < 0) or (vasen < 0)) {
        return false;
    }
    else {
        return true;
    }
}

// Tarkistetaan, etta palassa on vain sallittuja merkkeja
// Palautetaan true tai false
bool merkit(string pala) {
    string sallitut_merkit{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWX"
                           "YZ0123456789+-*/\\|<>#@ "};
    for (char& c: pala){
        if (sallitut_merkit.find(c) == string::npos) {
            return false;
        }
        else {
            return true;
        }
    }
}

// Tarkistetaan, etta kuva on oikean kokoinen
// Palautetaan true tai false
bool kuvan_koko(string pala) {
    if (pala.length() == 9) {
        return true;
    }
    // Jos kuvan pituus on 10, viimeisen merkin on oltava =
    else if (pala.length() == 10) {
        if (pala.at(9) == '=') {
            return true;
        }
    }
    else {
        return false;
    }
}

// Tarkistetaan, etta nollia on max 2kpl ja ne eivat ole vastakkain
bool nollat(Pala& pala, int ylos, int oikea, int alas, int vasen) {
    if (pala.laske_nollat() > 2) {
        return false;
    }
    else {
        if (((ylos == 0) and (alas == 0)) or ((vasen == 0) and (oikea == 0))) {
            return false;
        }
        else {
            return true;
        }
    }
}

// Lasketaan niiden palojen maara, jotka kuuluisi laittaa vasempaan ylakulmaan
int ylakulma_tarkistus(Pala pala, int ylakulma) {
    string kuva = pala.kuva();
    if (kuva.length() == 10) {
        if (kuva.at(9) == '=') {
            ++ylakulma;
        }
    }
    return ylakulma;
}

// Lasketaan palan nollien maara
int nollien_maara(Pala pala, int nollat) {
    nollat += pala.laske_nollat();
    return nollat;
}

// Tarkistetaan, etta kaikkia reunoja, jotka != 0, on tasan 2kpl
bool sisareunojen_tarkistus(vector<int> reunat) {
    for (unsigned i=0; i < reunat.size() ; ++i) {
        if (count(reunat.begin(), reunat.end(), reunat.at(i)) != 2) {
            return false;
        }
        else {
            return true;
        }
    }
}
