#ifndef PALAT_HH
#define PALAT_HH

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Luokka Pala, jonka avulla käyttäjän luomia palapelin paloja käsitellään
class Pala {
    public:
        Pala(const string& merkkijono);
        vector<string> luo_pala(const string& merkkijono);
        int reunanro(const int& sijainti);
        string kuva();
        int laske_nollat();
        void kierra();
        void kaytetty();
        bool getKaytetty() const;
        void tulosta(int rivi) const;

    private:
        vector<string> pala_; // Vektori, johon tallennetaan palan tiedot
        bool kaytetty_;

};

#endif // PALAT_HH
