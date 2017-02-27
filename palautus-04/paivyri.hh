#ifndef PAIVYRI_HH
#define PAIVYRI_HH

#include <string>
#include <memory>
#include "paivays.hh"

using namespace std;

class Tapahtumat {
  public:
    Tapahtumat();
    void tulosta() const;
    bool lisaa_tapahtuma(const string& syote);
    bool poista();
    bool talleta(const string& paivam, ofstream& tiedosto);

  private:
    struct Tapahtuma {
        void tulosta() const;
        string tapahtuma_;
        shared_ptr<Tapahtuma> seurOsoit;
    };

    shared_ptr<Tapahtuma> ekaOsoit_;
    shared_ptr<Tapahtuma> vikaOsoit_;
};

class Paivyri {
  public:
    Paivyri();
    bool lisaa_tapahtuma(const string& paivamaara, const string& kuvaus);
    void tulosta() const;
    bool nayta(const string& pvm);
    bool poista(const string& pvm);
    bool talleta(const string& tiedostonimi);

  private:
    struct Paiva {
        Paivays paiv;
        shared_ptr<Paiva> seurOsoit;
        Tapahtumat tapahtuma;
        unsigned koko_;
    };

    shared_ptr<Paiva> ekaOsoit_;
    shared_ptr<Paiva> vikaOsoit_;
};


#endif
