// Moduuli: muunnossaannot / tiedosto: saannot.cpp
// Moduulin muunnossaannot toteutustiedosto:
// sisältää muunnokset-luokan metodit.

#include "muunnossaannot.hh"

using namespace std;

Muunnokset::Muunnokset(string yksikko, vector<double> luvut):
    muunnos_{luo_muunnos(yksikko, luvut)} {
}

// Luo olion, joka sisältää yksikön ja sitä vastaavat lukuarvot
map<string, vector<double>> Muunnokset::luo_muunnos(string yksikko, vector<double> luvut) {
    map<string, vector<double>> muunnos;
    muunnos.insert({yksikko, luvut});
    return muunnos;
}

// Lisää valmiiseen olioon uuden hakuavain-hyötytieto -parin
void Muunnokset::lisaa_muunnos(string yksikko, vector<double> luvut) {
    muunnos_.insert({yksikko, luvut});
}

// Etsii oliosta halutun hakuavaimen, eli yksikön
bool Muunnokset::etsi_luvut(string lahto) {
    map<string, vector<double>>::iterator iter;
    iter = muunnos_.begin();

    while (iter != muunnos_.end()) {
        if (iter->first == lahto) {
            return true;
        }
        ++iter;
    }
    return false;
}

// Hakee oliosta hakuavainta vastaavan hyötytiedon, eli kertoimen ja vakion
vector<double> Muunnokset::hae_luvut(string lahto) {
    map<string, vector<double>>::iterator iter;
    iter = muunnos_.begin();

    while (iter->first != lahto) {
        ++iter;
    }

    return iter->second;
}

