// Moduuli: tiedoston luku / tiedosto: tiedoston_luku.hh
// Moduulin tiedoston luku esittelytiedosto:
// sisältää esittelyn tiedoston lukemiseen tarkoitetulle funktiolle.

#ifndef TIEDOSTON_LUKU_HH
#define TIEDOSTON_LUKU_HH

#include "muunnossaannot.hh"
#include <string>
#include <map>

using namespace std;

bool lue_tiedosto(const string& syotetiedosto, map<string, Muunnokset>& saannot);

#endif // TIEDOSTON_LUKU_HH
