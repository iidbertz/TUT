// Moduuli: muunnossaannot / tiedosto: saannot.hh
// Moduulin muunnossaannot esittelytiedosto:
// sisältää muunnokset-luokan esittelyn.

#ifndef MUUNNOSSAANNOT_HH
#define MUUNNOSSAANNOT_HH

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Muunnokset {
  public:
    Muunnokset(string yksikko, vector<double> luvut);
    map<string, vector<double>> luo_muunnos(string yksikko, vector<double> luvut);
    void lisaa_muunnos(string yksikko, vector<double> luvut);
    bool etsi_luvut(string lahto);
    vector<double> hae_luvut(string lahto);
  private:
    map<string, vector<double>> muunnos_;
};

#endif // MUUNNOSSAANNOT_HH
