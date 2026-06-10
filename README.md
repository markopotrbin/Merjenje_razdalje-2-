# Kratek opis
Izdelala sva merilno napravo za merjenje dolžine. Uporabila sva laserski senzor _VL53L1X_, TFT zaslon _1.8"TFT128*RGB*160_ in mikrokrmilnik ESP8266.

Najprej sva se dogovorila kateri senzor za merjenje dolžine bova uporabila. Izbirala sva med ultrazvočnim (HC - SR04) in laserskim (VL53L1X) senzorjem. Odločila sva se za laserskega, ker je natančnejši in ima manj tolerance (± 2 / 3 mm). 

# Kosovnica
Vsi elementi in komponente, ki sva jih uporabila:

- ESP8266

- Zaslon: 1.8"TFT128*RGB*160

- Senzor: VL53L1X

- Povezovalne žice

- Rjavi filament za 3D print in

- 9 V baterija.

# Vezalna shema
Prva slika vezalne sheme je narisana z ESP8266, ki uporablja GPIO pine.

<img width="741" height="363" alt="image" src="https://github.com/user-attachments/assets/fe6088ce-8206-4cb9-bffc-4496de94fbf2" />


Druga slika vezalne sheme je narisana z ESP8266, ki uporablja pine od D0 - D8.

<img width="811" height="397" alt="image" src="https://github.com/user-attachments/assets/588cef75-bbf3-4262-afce-b3e7a7d6299d" />

# Prototip vezave za merilnik

To je slika vezave, kjer sva vse elemente dala na testno ploščo (protoboard). Nato sva vse povezala z povezovalnimi žicami, da vidiva, če vse komponente delajo tako kot morajo. Nato sva popravljala in nadgrajevala kodo.

<img width="1024" height="768" alt="Slika vezave" src="https://github.com/user-attachments/assets/f91174e9-2f8b-4a19-97e6-117215b3c268" />

# Ohišje

<img width="937" height="741" alt="image" src="https://github.com/user-attachments/assets/c1fff4d9-eceb-49eb-8958-f9a2de8c63c8" />

<img width="1776" height="823" alt="image" src="https://github.com/user-attachments/assets/1e7e3768-3c9e-40a3-8949-b2e7a492c8b7" />

# Slika končnega izdelka

<img width="1601" height="1481" alt="Image (4)" src="https://github.com/user-attachments/assets/6819a4b6-4ea0-47ea-96c0-c75d555e2e33" />

# Posnetek delovanja naprave
Naprava dela bezhibno in tako kot mora. Pri izdelavi te naprave sva imela nekaj zežav s spajkanjam in ohišjem, ker nisva natančno izmerila komponent, zato sva morala potem to popraviti. Vesela sva, da nama je ta projetk vsel in da sva dosegla vse cilje, ki sva si jih zadala.



# A - test

<img width="1804" height="2573" alt="Image (6)" src="https://github.com/user-attachments/assets/f876b70c-d2b3-4ef0-a12f-de2fdf0544ab" />

# Komentar
Čeprav naprava danes deluje brezhibno, pot do končnega izdelka ni bila lahka. Soočila sva se z večjimi izzivi na treh glavnih področjih:

1. **Težave s pisanjem kode:** Na začetku koda sploh ni delovala pravilno. Imela sva težave z uvozi knjižnic in pravilno določitvijo zaslona ter senzorja. Meritve so nihale, zaslon se ni pravilno osveževal, zato sva morala kodo večkrat popolnoma spremeniti, dodati vzorčenje (povprečje 50 meritev) in ročno kalibrirati odstopanja za različna območja (do 20 cm, do 30 cm in nad 30 cm). //POPRAVI
2. **Težave z ohišjem:** Pri prvem načrtovanju ohišja nisva dovolj natančno izmerila vseh fizičnih komponent. Ko je bil tisk končan, sva ugotovila, da zaslon in baterija ne sežeta na svoja mesta, žice pa so bile preveč stisnjene. Ohišje sva morala popraviti in ga natisniti ponovno.

Kljub vsem oviram sva izjemno vesela, da nama je projekt uspelo pripeljati do konca, saj sva se skozi te napake ogromno naučila o praktičnem reševanju inženirskih problemov.


# Možne izboljšave
Boljši senzor, lahko bi naredila boljše ohišje.
