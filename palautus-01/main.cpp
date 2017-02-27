// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Palautustehtävä T1
// 240482 ida.myller@student.tut.fi (15.0 h)
//
// Ohjelma muodostaa käyttäjän komennon mukaisen palapelin palan. Paloja voi olla kerrallaan max 2 kpl.
// Palaa voi kääntää 90 astetta kerrallaan myötäpäivään ja sen voi korvata uudella palalla.
// Kaksi palaa voi liittää yhteen, mikäli vasemman palan oikeaa laitaa vastaa va laita löytyy oikeasta palasta.

#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<string> luo_pala(const string& merkkijono);

// Luokka Pala, jonka avulla käyttäjän luomia palapelin paloja käsitellään
class Pala {
    public:
        Pala(const string& merkkijono);
        bool tarkista_pala() const;
        void muuta_pala(vector<string> uusi_pala);
        void tulosta() const;
        void kierra();
        void rinnakkain(Pala& toinen_pala);

    private:
        vector<string> pala_; // Vektori, johon tallennetaan palan tiedot

};


int main()
{
    // Luodaan kaksi palaoliota, jotka tallennetaan palat-nimiseen vektoriin
    Pala pla1{""};
    Pala pla2{""};
    vector<Pala> palat;
    palat.push_back(pla1);
    palat.push_back(pla2);

    while (true) {
        // Pyydetään käyttäjältä komentoa aina edellisen suorituksen päätyttyä niin kauan, kunnes syötetään tyhjä rivi
        cout << "komento> ";
        string komento;
        getline(cin, komento);

        if (komento == ("")){
            break;
        }

        // Etsitään 1. välin paikka, jota ennen on määritelty tehtävä
        // ja sen jälkeen palan numero, jolle tehtävä suoritetaan
        unsigned indeksi = komento.find(" ");
        string tehtava = komento.substr(0, indeksi);
        string pala = komento.substr(indeksi+1, 1);

        // Muutetaan palan numero int-muotoon
        // Lähde: http://www.cplusplus.com/forum/general/13135/
        int pala_nro = atoi(pala.c_str());

        // Palan numero voi olla 1 tai 2
        if ((pala_nro > 0) and (pala_nro < 3)){
            // Tarkistetaan, onko pala olemassa
            bool tarkistettu_pala = palat.at(pala_nro-1).tarkista_pala();

            // Jos palaa ei ole mutta sitä yritetään käsitellä, tulostetaan virheilmoitus
            if ((tarkistettu_pala == true) and (tehtava != "pala")){
                cout << "Virhe: Palaa ei ole." << endl;
            }
            // Jos komento on pala, muodostetaan käyttäjän haluama pala
            else if (tehtava == "pala"){
                string palan_tiedot = komento.substr(indeksi+3);
                vector<string> uusi_pala = luo_pala(palan_tiedot);

                // Tallennetaan palan laidat int-muotoon
                int ylos = atoi(uusi_pala.at(0).c_str());
                int oikea = atoi(uusi_pala.at(1).c_str());
                int alas = atoi(uusi_pala.at(2).c_str());
                int vasen = atoi(uusi_pala.at(3).c_str());

                // Jos jokin näistä on negatiivinen, tulostetaan virheilmoitus
                if ((ylos < 0) or (oikea<0) or (alas < 0) or (vasen < 0)) {
                    cout << "Virhe: virheellinen syote" << endl;
                }
                else if ((uusi_pala.size() == 5) and (uusi_pala.at(4).length() == 9)){
                    palat.at(pala_nro-1).muuta_pala(uusi_pala);
                    cout << "Pala " << pala << " asetettu." << endl;
                } else {
                    cout << "Virhe: virheellinen syote" << endl;
                }
            }
            // Jos komento on kierrä, kutsutaan palan kiertävää funktiota
            else if (tehtava == "kierra"){
                palat.at(pala_nro-1).kierra();
                cout << "Palaa " << pala << " kierretty." << endl;
            }
            // Jos komento on tulosta, kutsutaan palan tulostavaa funktiota
            else if (tehtava == "tulosta"){
                palat.at(pala_nro-1).tulosta();
            }
            // Jos komento on rinnakkain, tarkistetaan voiko palat asettaa rinnakkain ja suoritetaan toiminto mikäli mahdollista
            else if (tehtava == "rinnakkain"){
                // Tallennetaan muuttujaan pala_2_nro liitettävän palan numero int-muodossa
                string pala_2 = komento.substr(indeksi+3, 1);
                int pala_2_nro = atoi(pala_2.c_str());

                // Tarkistetaan, onko liitettävä pala luotu
                bool tarkistettu_pala = palat.at(pala_2_nro-1).tarkista_pala();

                if (tarkistettu_pala == true){
                    cout << "Virhe: Palaa ei ole." << endl;
                }
                else if ((pala_2_nro > 0) and (pala_2_nro < 3) and (pala_nro != pala_2_nro)){
                    palat.at(pala_nro-1).rinnakkain(palat.at(pala_2_nro-1));
                }
                else {
                    cout << "Virhe: Virheellinen syote" << endl;
                }
            } else {
                cout << "Virhe: Virheellinen syote" << endl;
            }
        } else {
            cout << "Virhe: Virheellinen syote" << endl;
        }

    }
}

// Rakentajafunktio
Pala::Pala(const string& teksti):
    pala_{luo_pala(teksti)}{
}

// Tarkistaa, onko pala olemassa
bool Pala::tarkista_pala() const{
    if (pala_.size() == 5){
        return false;
    }
    else {
        return true;
    }
}

// Muuttaa palan arvot uuden palan arvoiksi
void Pala::muuta_pala(vector<string> uusi_pala){
    pala_ = uusi_pala;
}

// Tulostaa halutun palan
void Pala::tulosta() const {
    // Ensin tulostetaan palan laidat sijainteineen
    cout << "ylos:" << pala_.at(0) << endl << "oikea:" << pala_.at(1) << endl
    << "alas:" << pala_.at(2) << endl << "vasen:" << pala_.at(3) << endl;
    string rivi = pala_.at(4);
    // Seuraavaksi tulostetaan itse pala
    int laskuri = 0;
    for (char& c: rivi){
        cout << c ;
        laskuri += 1;
        if (laskuri == 3){
            cout << endl;
            laskuri = 0;
        }
    }
}

// Kiertää palaa muuttamalla palan vektoria
void Pala::kierra(){
    // Kierretaan ensin palan laidat
    string eka_laita = pala_.at(0); // Tallennetaan 1. laita muuttujaan talteen
    pala_.at(0) = pala_.at(3);
    pala_.at(3) = pala_.at(2);
    pala_.at(2) = pala_.at(1);
    pala_.at(1) = eka_laita; // Sijoitetaan muuttujaan tallennettu laita viimeisenä
    // Seuraavaksi kierretään itse pala
    string vanha_pala = pala_.at(4);
    string uusi_pala{""};
    // Määritellään rotate-vektoriin palan merkkien uudet paikat
    vector<int> rotate{6,3,0,7,4,1,8,5,2};

    for (int i = 0; i < 9; ++i){
        int indeksi = rotate.at(i);

        // Määritellään merkkien -, |, / ja \ kääntäminen
        if (vanha_pala.at(indeksi) == '-'){
            vanha_pala.at(indeksi) = '|';
        }else if (vanha_pala.at(indeksi) == '|'){
            vanha_pala.at(indeksi) = '-';
        }else if (vanha_pala.at(indeksi) == '/'){
            vanha_pala.at(indeksi) = '\\'; // '\\' koska '\' tuotti virheen (väitti toisen '-merkin puuttuvan)
        }else if(vanha_pala.at(indeksi) == '\\'){
            vanha_pala.at(indeksi) = '/';

        }uusi_pala.push_back(vanha_pala.at(indeksi));
    }pala_.at(4) = uusi_pala;
}

// Käsitellään komento rinnakkain tarkistamalla, onko se mahdollista ja suorittamalla se mikäli on
void Pala::rinnakkain(Pala& toinen_pala ) {
    // Käydään läpi kaikki jälkimmäisen palan laidat
    for ( int i = 0; i < 4 ; ++i ){
        // Jos jokin laidoista täsmää ensimmäisen palan oikeaan laitaan, kierretään jälkimmäinen sopimaan siihen
        if (pala_.at(1) == toinen_pala.pala_.at(i)) {
            for (; i < 3; ++i){
                toinen_pala.kierra();
            }
            // Tulostetaan palat rinnakkain mikäli mahdollista
            string pala1 = pala_.at(4);
            string pala2 = toinen_pala.pala_.at(4);
            cout << pala1.substr(0,3) << pala2.substr(0,3) << endl;
            cout << pala1.substr(3,3) << pala2.substr(3,3) << endl;
            cout << pala1.substr(6) << pala2.substr(6) << endl;
            return;
        }
    }cout << "Virhe: Palat eivat sovi yhteen!" << endl; // Virheilmoitus jos paloja ei voi sovittaa yhteen
}

// Luodaan uusi pala käyttäjän syöttämästä merkkijonosta
vector<string> luo_pala(const string& merkkijono) {
    vector<string> valmis_pala;
    string kentan_sisalto{""};

    for ( unsigned i = 0; merkkijono.length() > i;  ++i) {

        if ( merkkijono.at(i) != ':' ) {
            kentan_sisalto.push_back( merkkijono.at(i) );
        }
        else {
            valmis_pala.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }
    }
    valmis_pala.push_back(kentan_sisalto);

    return valmis_pala;
}
