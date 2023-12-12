/* 
C++-ohjelmoinnin perusteet syksy 2023 (5G00EI63-3011)

HARJOITUSTY÷ (HOTELLIHUONE)

NIMI:               Jaakko Simonen
LUOKKA:             23TIETOB
SƒHK÷POSTI:         jaakko.simonen@tuni.fi
OPISKELIJANUMERO:   2307580

OHJELMAN KUVAUS:

T‰m‰ ohjelma sis‰lt‰‰ toiminnallisuudet hotellihuoneiden varaukseen.
Asiakas voi valita tai arpoa hotellihuoneen, syˆtt‰‰ yˆpymisp‰ivien m‰‰r‰n
ja saada laskennallisen hinnan varatusta huoneesta.
Ohjelman toimintaa jatketaan niin kauan kuin asiakkaita riitt‰‰.
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>

const int HUONEITA_MIN = 40;  // Arvotun huonem‰‰r‰n alaraja
const int HUONEITA_MAX = 300; // Arvotun huonem‰‰r‰n yl‰raja
//const int HOTELLIYON_HINTA_1HLO{ 100 }; // Hotelliyˆn hinta yhden hengen huoneissa
//const int HOTELLIYON_HINTA_2HLO{ 150 }; // Hotelliyˆn hinta kahden hengen huoneissa

bool syotteenTarkistus(std::string syote, std::string sallitut_merkit, bool vain_yksi_merkki)
{
    if (vain_yksi_merkki)
    {
        if (syote.length() > 1)
        {
            std::cout << "Syˆtteesi on virheellinen.\n";
            std::cout << "Kirjoita vain yksi merkki.\n" << std::endl;
            return false;
        }
        else
        {
            const char vastaus{ syote[0] };
            for (int n{ 0 }; n < sallitut_merkit.size(); n++)
            {
                if (vastaus == sallitut_merkit[n])
                {
                    return true;
                }
                else
                {
                    continue;
                }
                // Tulosta virheilmoitus
                std::cout << "Syˆtteesi on virheellinen.\n";
                std::cout << "Sallitut merkit ovat:\n";
                for (int n{ 0 }; n < sallitut_merkit.size(); n++)
                {
                    std::cout << sallitut_merkit[n] << " ";
                }
                std::cout << "\n\n";
                return false;
            }
        }

    }
    // Jos syˆte voi olla useamman merkin mittainen, tarkistetaan syˆtteen jokainen merkki,
    // onko se sallittujen merkkien joukossa.
    else
    {
        for (int i{ 0 }; i < syote.length(); i++)
        {
            for (int k{ 0 }; k < sallitut_merkit.length(); k++)
            {
                if (syote[i] == sallitut_merkit[k])
                {
                    return true;
                }
            }
        }

    }
    // tulosta virheilmoitus
    std::cout << "Syˆtteesi on virheellinen.\n";
    std::cout << "Sallitut merkit ovat:\n";
    for (int n{ 0 }; n < sallitut_merkit.size(); n++)
    {
        std::cout << sallitut_merkit[n] << " ";
    }
    std::cout << "\n\n";
    return false;
}

std::string kysySyote(std::string kysymys, std::string sallitut_merkit, bool vain_yksi_merkki)
{
    std::string vastaus{ "" };
    while (true)
    {
        std::cout << kysymys << std::endl;
        std::cin >> vastaus;
        std::cout << std::endl;
        if (!syotteenTarkistus(vastaus, sallitut_merkit, vain_yksi_merkki))
        {
            continue;
        }
        else
        {
            return vastaus;
        }

    }

}

class Hotellihuone {
public:
    int huonenumero{ 0 };
    int huonekoko{ 0 };
    bool vapaa{ true };

    void varaa_huone() {
        vapaa = false;

        // Kysyt‰‰n k‰ytt‰j‰lt‰ hotellissa nukuttujen ˆiden lukum‰‰r‰‰
        std::string vastaus = kysySyote("Kuinka monta yˆt‰ haluatte nukkua hotellissa?: ", "0123456789", false);
        int nukutut_yot = std::stoi(vastaus);

        // Huonekoon mukaisten hintojen m‰‰ritys
        int hinta_per_yo;
        if (huonekoko == 1) {
            hinta_per_yo = HOTELLIYON_HINTA_1HLO;
        }
        else if (huonekoko == 2) {
            hinta_per_yo = HOTELLIYON_HINTA_2HLO;
        }
        else {
            // Jos huonekoko ei ole 1 tai 2, k‰ytet‰‰n oletushintaa
            hinta_per_yo = HOTELLIYON_OLETUSHINTA;
        }

        // Lasketaan ja ilmoitetaan hinta
        int hinta = nukutut_yot * hinta_per_yo;

        // Alennuksen m‰‰ritys
        double alennus = arvoSatunnainenAlennus();
        int alennettu_hinta = static_cast<int>(hinta * (1.0 - alennus));

        std::cout << "Hotellissa nukuttujen ˆiden alkuper‰inen hinta olisi ollut " << hinta << " Ä.\n";
        std::cout << "Alennettu hinta on " << alennettu_hinta << " Ä.\n\n";
    }

private:
    const int HOTELLIYON_HINTA_1HLO{ 100 };
    const int HOTELLIYON_HINTA_2HLO{ 150 };
    const int HOTELLIYON_OLETUSHINTA{ 120 };  // Oletushinta muille huoneille

    double arvoSatunnainenAlennus() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 2);

        int satunnaisluku = dis(gen);

        if (satunnaisluku == 0) {
            return 0.0;
        }
        else if (satunnaisluku == 1) {
            return 0.1;
        }
        else {
            return 0.2;
        }
    }
};



std::vector<Hotellihuone> luoHotellihuoneet()
{
    std::vector<Hotellihuone> hotellihuoneet;

    std::random_device satunnaislaite;// Satunnaislukugeneraattorin alustus
    std::mt19937 generaattori(satunnaislaite()); // Mersenne Twister -generaattori
    //
    std::uniform_int_distribution<> jakauma(HUONEITA_MIN / 2, HUONEITA_MAX / 2);  // Tasainen jakauma v‰lill‰ [20, 150]
    
    // Generoidaan hotellihuoneiden lukum‰‰‰r‰ tasajakaumasta, ja kerrotaan se kahdella niin kaikki mahdolliset arvot ovat parillisia.
    const int HUONEMAARA{ jakauma(generaattori)*2};

    for (int i{ 0 }; i < HUONEMAARA / 2; i++)
    {
        Hotellihuone huone;
        huone.huonenumero = i + 1;
        huone.huonekoko = 1;
        huone.vapaa = true;
        hotellihuoneet.push_back(huone);
    }
    for (int i{ HUONEMAARA / 2}; i < HUONEMAARA; i++)
    {
        Hotellihuone huone;
        huone.huonenumero = i + 1;
        huone.huonekoko = 2;
        huone.vapaa = true;
        hotellihuoneet.push_back(huone);
    }
    return hotellihuoneet;
}





bool asiakkaitaSaapuu()
{   
    // T‰m‰ funktio suoritetaan, kun halutaan tiet‰‰ saapuuko hotelliin uusia asiakkaita.
    std::string valinta{ "" };
    // Ky
    valinta = kysySyote("Saapuuko hotelliin asiakkaita? (k)=kyll‰, (e)=ei", "ke", true);
    // Tehd‰‰n syˆtteentarkastus, ja ilmoitetaan k‰ytt‰j‰lle, jos syˆte on virheellinen.
    // Jatketaan, syˆtteen kysymist‰, kunnes saadaan kyll‰- tai ei-vastaus. ("k" tai "e")
    if (valinta == "k")
    {
        return true;
    }
    else
    {
        return false;
    } 
}

void otaAsiakasVastaan()
{
    std::cout << "Tervetuloa hotelliin!\n";
}

bool huoneHalutaanVarata()
{
    // Halutaanko huone varata?
    std::string valinta{ "" };
    // Tehd‰‰n syˆtteentarkastus, ja ilmoitetaan k‰ytt‰j‰lle, jos syˆte on virheellinen.
    // Jatketaan, syˆtteen kysymist‰, kunnes saadaan kyll‰- tai ei-vastaus. ("k" tai "e")
    valinta = kysySyote("Haluatteko varata huoneen? (k)=kyll‰, (e)=ei", "ke", true);
    if (valinta == "k")
    {
        return true;
    }
    else
    {
        std::cout << "Kiitos ja hyv‰‰ p‰iv‰njatkoa!\n\n";
        return false;
    }
}

int valitseHuone(std::vector<Hotellihuone>& hotellihuoneet, int huonekoko) // Viitataan vektoriin hotellihuoneet, jotta siihen voi tehd‰ muutoksia.
{
    //
    std::string valinta{ "" };
    while (true)
    {
        int huonenumero{ 0 };
        // Pyydet‰‰n asiakasta valitsemaan huonenumero
        if (huonekoko == 1)
        {
            std::string kysymys{ "Ole hyv‰ ja valitse huonenumero (1-" + std::to_string(hotellihuoneet.size() / 2) + ")" };
            valinta = kysySyote(kysymys, "0123456789", false);
            huonenumero = std::stoi(valinta);
            if (huonenumero < 1 || huonenumero > hotellihuoneet.size() / 2)
            {
                std::cout << "Huonenumeron pit‰‰ olla v‰lilt‰ 1-" << hotellihuoneet.size() / 2 << "!\n\n";
                continue;
            }
        }
        else
        {
            std::string kysymys{    "Ole hyv‰ ja valitse huonenumero (" + std::to_string(hotellihuoneet.size() / 2 + 1)
                                    + "-" + std::to_string(hotellihuoneet.size()) + ")" };
            valinta = kysySyote(kysymys, "0123456789", false);
            huonenumero = std::stoi(valinta);
            if (huonenumero < hotellihuoneet.size() / 2 + 1 || huonenumero > hotellihuoneet.size())
            {
                std::cout << "Huonenumeron pit‰‰ olla v‰lilt‰ " << hotellihuoneet.size() / 2 + 1 << "-" << hotellihuoneet.size() << "!\n\n";
                continue;
            }
        }
        
        
        
        // Tarkistetaan, ett‰ asiakkaan pyyt‰m‰ huone on olemassa
        // Kaikkia syˆtetarkastuksia ei valitettavasti saa yhden funktion sis‰lle
        {
            for (int indeksi{ 0 }; indeksi < hotellihuoneet.size(); indeksi++)
            {
                if (hotellihuoneet[indeksi].huonenumero == huonenumero)
                {
                    // Jos huone on varattu, asiakkaan t‰ytyy valita uusi huone.
                    if (!hotellihuoneet[indeksi].vapaa)
                    {
                        std::cout << "Huone on valitettavasti jo varattu.\n";
                        std::cout << "Valitse toinen huone.\n";
                        break;
                    }
                    else
                    {
                        
                        std::cout << "Valitsemanne huone sattuu sopivasti olemaan vapaana.\n";

                        
                        return indeksi;
                    }
                }
            }
        }
    }
    
}

int arvoHuone(std::vector<Hotellihuone>& huoneluettelo, int huonekoko)
{
    // Luo satunnaislukugeneraattori
    std::random_device rd;
    std::mt19937 generator(rd());

    // M‰‰rit‰ satunnaislukujen jakauma puoliskoille
    std::uniform_int_distribution<int> distribution;
    if (huonekoko == 1) {
        distribution = std::uniform_int_distribution<int>(0, huoneluettelo.size() / 2 - 1);
    }
    else if (huonekoko == 2) {
        distribution = std::uniform_int_distribution<int>(huoneluettelo.size() / 2, huoneluettelo.size() - 1);
    }
    else {
        // Huonekoko ei ole 1 tai 2, palauta virheellinen arvo
        std::cerr << "Virheellinen huonekoko\n";
        return -1;
    }

    // Arvo satunnainen huoneen indeksi
    int indeksi = distribution(generator);

    // Tarkista, ett‰ huone on vapaa
    while (!huoneluettelo[indeksi].vapaa)
    {
        // Jos huone ei ole vapaa, arvo uusi indeksi
        indeksi = distribution(generator);
    }

    // Ilmoita asiakkaalle valitusta huoneesta
    std::cout << "Arvottiin huone numero " << huoneluettelo[indeksi].huonenumero << ".\n";

    // Palauta valitun huoneen indeksi
    return indeksi;
}

void varaaHuone(std::vector<Hotellihuone>& huoneluettelo)
{
    // TODO: Kysy haluaako asiakas valita huonenumeron itse.
    // TODO:    Toteuta ehtolause, joka joko kutsuu arvoHuone()-nimist‰ funktiota
    //          tai valitseHuone()-nimist‰ funktiota asiakkaan toiveen mukaan.
    // TODO: Ehtolause tallettaa valitun funktion paluuarvon muuttujaan int indeksi, kuten alla.

    // Jos asiakas haluaa valita huoneen itse, annetaan h‰nen valita huone
    int huonekoko{ std::stoi(kysySyote("Haluatteko yhden (1) vai kahden (2) hengen huoneen? (1/2)", "12", true)) };
    std::string valinta = kysySyote("Haluatteko valita huonenumeron itse? (k/e)", "ke", true);
    int indeksi;

    if (valinta == "k")
    {
        indeksi = valitseHuone(huoneluettelo, huonekoko);
    }
    else
    {
        indeksi = arvoHuone(huoneluettelo, huonekoko);
    }
    huoneluettelo[indeksi].varaa_huone();
}

void alkuhopinat()
{
    // T‰m‰ funktio suoritetaan, kun ohjelman suoritus alkaa, ja hotelli avaa ovensa
    std::cout << "Hotelli avaa ovensa.\n";
    std::cout << "Hotelliin voi nyt saapua asiakkaita \n\n";
}

void loppukaneetti()
{
    // T‰m‰ funktio suoritetaan, kun ohjelman suoritus p‰‰ttyy, ja hotelli sulkee ovensa.
    std::cout << std::endl;
    std::cout << "Hotelliin ei n‰yt‰ saapuvan uusia asiakkaita.\n";
    std::cout << "Hotellin vastaanotto sulkeutuu t‰lt‰ p‰iv‰lt‰, ja hotellin ovet suljetaan.\n" << std::endl;
    std::cout << "Kiitos ohjelman suorittamisesta!\n";
    std::cout << "N‰kemiin!\n";
}


int main()
{
    // Rakennetaan hotelli, ja tehd‰‰n sinne tarvittava m‰‰r‰ huoneita.
    std::vector<Hotellihuone> hotelli{ luoHotellihuoneet()};

    alkuhopinat();

    // Niin kauan kuin asiakkaita saapuu, yritet‰‰n ottaa asiakkaat vastaan
    // Jos asiakkaita ei saavu, lopetetaan ohjelman suorittaminen
    while (asiakkaitaSaapuu())
    {
        // Otetaan uusi asiakas vastaan
        otaAsiakasVastaan();

        // Kysyt‰‰n varaako asiakas huoneita.
        // Jos ei varaa, siirryt‰‰n seuraavaan asiakkaaseen:
        // Jos uusia asiakkaita ei tule, ohjelman suoritus p‰‰ttyy.
        if (!huoneHalutaanVarata())
        {
            // Palataan silmukan ehtoon, jossa tarkistetaan saapuuko uusia asikkaita
            continue;
        }
        
        // Pyydet‰‰n asiakasta varaamaan huone
        varaaHuone(hotelli);
    }
    
    
    // Kirjoitetaan loppukaneetit
    loppukaneetti();

}

