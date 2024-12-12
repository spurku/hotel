# hotellihuone varausjärjestelmä

Janne Lankinen 
Tampereen ammattikorkekoulu TAMK
24TIETOA

Arvosana arvio 4

Hotellihuoneiden hallintaan tarkoitettu c++ sovellus, joka mahdollistaa huoneiden varaamisen, tarkastelun ja tietojen tallentamisen tiedostoon. Käyttäjäystävällisessä           tekstipohjaisessa käyttöliittymässä voi valita toimintoja, kuten huonelistauksen näyttäminen, huoneiden varaaminen ja ohjelman sulkeminen. 

  Keskeiset Ominaisuudet

  - Huoneiden Lataaminen ja Alustaminen

    Tiedot ladataan tiedostosta ohjelman käynnistyessä.
    Jos tiedostoa ei löydy, huoneet alustetaan satunnaisesti (30–50 huonetta, hinnat 80–100 €/yö).
    Huonelistauksen Näyttäminen

  -Näyttää huonenumero, varaustilanne ja hinta per yö.

Huoneiden Varaaminen

  - Käyttäjä valitsee huonenumeron ja öiden määrän.
Varaus estetään, jos huone on jo varattu tai syöte on virheellinen.
Varaus onnistuu oikeilla tiedoilla, ja ohjelma laskee kokonaishinnan.

Tietojen Tallennus

Varausten muutokset tallennetaan automaattisesti tiedostoon.

Virheenkäsittely

Käsittelee virheelliset syötteet ja ohjaa käyttäjän oikeaan toimintaan.

Mukautettavuus

Huonemäärä ja hintahaarukka säädettävissä ohjelman vakioista.

Tekniset Piirteet
Tiedostojen Käyttö: Käytetään std::ifstream ja std::ofstream, ja tiedostot tallennetaan helposti luettavaan muotoon.
Rakenteet: Huonetiedot tallennetaan Room-rakenteeseen.
Syötteen Käsittely: Virheellinen syöte käsitellään tarkasti (std::cin-virheenkäsittely).
Ohjelma on selkeä, skaalautuva ja toimiva ratkaisu hotellihuoneiden varaamiseen.

