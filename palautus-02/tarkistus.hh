#ifndef TARKISTUS_HH
#define TARKISTUS_HH

#include "palat.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool neg_reuna(int ylos, int oikea, int alas, int vasen);
bool merkit(string rivi);
bool kuvan_koko(string rivi);
bool nollat(Pala& pala, int ylos, int oikea, int alas, int vasen);
int ylakulma_tarkistus(Pala palat, int ylakulma);
int nollien_maara(Pala pala, int nollat);
bool sisareunojen_tarkistus(vector<int> reunat);

#endif // TARKISTUS_HH
