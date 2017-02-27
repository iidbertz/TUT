#ifndef KOKOAMINEN_HH
#define KOKOAMINEN_HH

#include "palat.hh"
#include <iostream>
#include <string>
#include <vector>

Pala vasen_ylakulma(vector<Pala>& palat);
Pala seuraava_pala_rivilla(vector<Pala>& palat, Pala edellinen);
Pala uusi_rivi(vector<Pala>& palat, Pala ylempi);

void tulostus(int leveys, vector<Pala> palapeli);

#endif // KOKOAMINEN_HH
