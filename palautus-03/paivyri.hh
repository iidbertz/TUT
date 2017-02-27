#ifndef PAIVYRI_HH
#define PAIVYRI_HH

#include <string>
#include <map>
#include <vector>
#include "paivays.hh"

using namespace std;

class Paivyri {
  public:
    bool lisaa_tapahtuma(const string& paivamaara, const string& kuvaus);
    void tulosta();
    void nayta(const string& pvm);
    void poista(const string& pvm);
    void talleta(const string& tiedostonimi);

    // Muita metodifunktioiden esittelyitä puuttuu tästä.

  private:
    map<Paivays, vector<string>> paivyridata_;

    // Jonkinlainen STL-map -rakenne tänne, johon eri päivämäärien
    // tapahtumien kuvaukset talletetaan.  Rakenteen on oltava sellainen
    // että hakuavaimena on Paivays-tyyppinen arvo, ja hyötykuormana
    // kaikki kyseiselle päivämäärälle kirjatut tapahtumien kuvaukset
    // nekin sopivassa säiliössä.
};

#endif
