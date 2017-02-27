// Moduuli: muunnoslasku / tiedosto: muunnoslasku.hh
// Moduulin muunnoslasku esittelytiedosto:
// sisältää esittelyt yksikkömuunnosten laskemista käsitteleville funktioille.

#ifndef MUUNNOSLASKU_HH
#define MUUNNOSLASKU_HH

#include "muunnossaannot.hh"
#include "apufunktiot.hh"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

void laske_muunnos(double arvo, string lahto, string kohde,
                   map<string, Muunnokset> saannot);
bool laske_suoraan(double arvo, string lahto, string kohde,
                   map<string, Muunnokset> saannot, double& tulos);
bool laske_kaantaen(double arvo, string lahto, string kohde,
                    map<string, Muunnokset> saannot, double& tulos);

#endif // MUUNNOSLASKU_HH
