// Moduuli: apufunktiot / tiedosto: apufunktiot.hh
// Moduulin apufunktiot esittelytiedosto:
// sisältää esittelyt avustaville funktioille, joiden sijoittaminen
// muihin moduuleihin ei tuntunut järkevältä.

#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include "muunnossaannot.hh"
#include "apufunktiot.hh"
#include <string>
#include <vector>
#include <map>

using namespace std;

string poista_valit(string rivi);
bool tulkitse_kaava(string rivi, string& lahtoyksikko, string& kohdeyksikko,
                    string& kerroin, string& vakio);
bool merkkien_tarkistus(string yksikko);
bool talleta_rivi(string lahtoyksikko, string kohdeyksikko, double kerroin,
                  double vakio, map<string, Muunnokset>& saannot);
bool etsi_kaava(string lahtoyksikko, string kohdeyksikko, map<string, Muunnokset> saannot);
bool tulkitse_syote(string& maara, string& lahto, string& kohde, string syoterivi);
bool tarkista_lukuarvo(string maara);
bool etsi_yksikko(string kohde, map<string, Muunnokset> saannot);

#endif // APUFUNKTIOT_HH
