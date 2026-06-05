# VIKO IS25SN AM PROJEKTINIS DARBAS
# Bibliotekos knygų apskaitos sistema
## Programos paskirtis
Bibliotekos knygų apskaitos sistema skirta bibliotekininkui valdyti bibliotekos knygų fondą. Programa leidžia 
registruoti naujas knygas, peržiūrėti naujas knygas, peržiūrėti ir redaguoti esamus įrašus, išduoti bei grąžinti knygas 
studentams, atlikti paiešką pagal įvairius skriterijus ir generuoti ataskaitas.

Programoje taip pat realizuota vartotojų prieigos valdymo sistema, paremta naudotojų vaidmenimis. Sistema išskiria
administratoriaus ir naudotojo paskyras. Administratoriai atsako už paskyrų administravimą: naujų paskyrų kūrimą, esamų
paskyrų redagavimą, blokavimą bei naudotojų vaidmenų keitimą. Naudotojo paskyra skirta bibliotekos knygų išteklių
valdymui, leidžianti vykdyti knygų registravimą, paiešką, išdavimą, grąžinimą ir ataskaitų formavimą.

Programa sukurta naudojant C++ programavimo kalbą ir duomenis saugo tekstiniame faile.

## Duomenų saugojimas
 Knygų duomenys saugomi faile:
>../DB/bookDataBase.

Vieno įrašo struktūra:
>Knygos pavadinimas;Autorius1|Autorius2;Metai;Kiekis;Studentas1|Studentas2

Pavyzdys:
>C++ FAQs;Marshall Cline|Greg Lomow|Mike Girou;1998;2;petrajtis

Kur:

**Knygos pavadinimas** - Knygos pavadinimas

**Autoriai** - Vienas ar keli autoriai

**Metai** - Laidos metai

**Kiekis** - Bendras kiekis / Prieinamas

**Studentai** - Studentų, pasiėmusių knygą, sąrašas

## Programos galimybės
### 1. Naujos knygos registravimas

Leidžia pridėti naują knygą į bibliotekos duomenų bazę.

Įvedami duomenys:
- knygos pavadinimas
- leidimo metai
- egzempliorių kiekis
- autorių skaičius
- autorių vardai ir pavardės.

#### Apsaugos
- leidžiama įvesti neribotą autorių skaičių
- palaikomi autoriai su tarpais
- knyga išsaugoma tik sėkmingai atidarius duomenų failą

### 2. Knygų peržiūra

Leidžia peržiūrėti visas bibliotekoje esančias knygas.

Atvaizduojama:
- Knygos eilės numeris
- pavadinimas
- autoriai
- leidimo metai
- prieinamų egzempliorių kiekis
- bendras egzempliorių kiekis.
#### Apsaugos
- jei knygų nėra, rodomas informacinis pranešimas
- teisingai apskaičiuojamas prieinamų egzempliorių kiekis.

### 3. Paieška pagal kriterijus
Galima ieškoti pagal:
1. Autorių
2. Knygos pavadinimą arba raktinį žodį
3. Leidimo metus.

Galima naudoti `nuo 1 iki 3` kriterijų.

#### Papildomos galimybės
Galima pasirinkti:
- ieškoti tarp visų knygų
- ieškoti tik tarp prieinamų knygų.

#### Apsaugos
- tas pats kriterijus negali būti pasirinktas du kartus
- paieška nepriklauso nuo didžiųjų ir mažųjų raidžių.

### 4. Knygos išdavimas studentui
Leidžia išduoti pasirinktą knygą studentui.

Įvedama:
- knygos eilės numeris
- studento kuriam išduoda pavardė

#### Apsaugos
- negalima išduoti knygos, jei nėra laisvų egzempliorių
- tas pats studentas negali pasiimti daugiau nei viena egzempliorių
- tikrinamas knygos prieinamumas.

### 5. Knygos grąžinimas
Leidžia grąžinti anksčiau išduotą knygą.

Įvedama:
- knygos numeris
- studento pavardė.

#### Apsaugos
- negalima grąžinti knygos, kuri nėra išduota
- tikrinama, ar studentas tikrai turi pasirinktą knygą
- apsaugoma nuo neegzistuojančių įrašų šalinimo.

### 6. Knygos redagavimas
Leidžia redaguoti:
- knygos pavadinimą
- autorius
- leidimo metus
- egzempliorių kiekį

#### Apsaugos
- negalima nustatyti mažesnio egzempliorių kiekio nei šiuo metu išduota studentams
- negalima pakeisti visą autorių sąrašą.

### 7. Knygos pašalinimas
Leidžia pašalinti knygą iš duomenų bazės.

#### Apsaugos
- negalima pašallinti knygos, kuri yra išduota studentams
- pirmiausia turi būti grąžinti visi egzemplioriai.

## Ataskaitų generavimas
### 1. Visų knygų ataskaita
Failai:
>Print_all_books.txt

Pateikiama:
- visų knygų informaciją
- bendras knygų kiekis
- bendras egzempliorių kiekis
- išduotų egzmepliorių kiekis
- prieinamų egzempliorių kiekis.

### 2. Išduotų knygų ataskaita
Failas:
>Print_issued_books.txt

Pateikiama:
- išduotos knygos
- studentų sąrašai
- bendras išduotų egzempliorių skaičius

### 3. Neprieinamų knygų ataskaita
Failas:
>Print_unavailable_books.txt

Pateikiama:
- knygos, kurių visi egzemplioriai yra išduoti
- bendras neprieinamų knygų skaičius.

# Naudotojų valdymo sistema

Programoje realizuota naudotojų autentifikavimo ir teisių valdymo 
sistema. Kiekviena paskyra turi unikalų naudotojo 
vardą, slaptažodį bei priskirtą vaidmenį.

## Paskyrų tipai

#### Administratorius
Administratoriaus paskyra turi išplėstas teises ir gali:
- kuri naujas naudotojų paskyras
- redaguoti esamų naudotojų duomenis
- keisti naudotojų vaidmenis
- blokuoti naudotojų paskyras
- peržiūrėti visų sistemos naudotojų sąrašą

#### Naudotojas
Naudotojo paskyra skirta bibliotekos veiklų vykdymui. Naudotojas gali:
- registruoti naujas knygas
- prežiūrėti knygų sąrašą
- vykdyti knygų paiešką pagal pasirinktus kriterijus
- išduoti knygas studentams
- priimti grąžinamas knygas
- redaguoti knygų duomenis
- šalinti knygų įrašus
- formuoti ataskaitas.

### Paskyrų duomenų saugojimas

Naudotojų paskyrų duomenys saugomi tekstiniame faile:
>../DB/ACC/ACC

Vieno įrašo struktūra:
>naudotojo_vardas;slaptažodis;rolė

Pavyzdys:
>administratorius;qwerty;a
> 
> naudotojas;12345;u

Kur:
- a - administratoriaus paskyra
- u - naudotojo paskyra
- b - užblokuota paskyra.

## Realizuotos apsaugos
Sistemoje įgyvendintos šios apsaugos priemonės:
- neleidžiama sukurti paskyros su jau egzistuojančiu naudotojo vardu
- naudotojų vardų palyginimas atliekamas neatsižvelgiant į didžiąsias ir mažąsias raides;
- užblokuotos paskyros negali prisijungti prie sistemos
- redaguojant paskyrą galima keisti tik pasirinktus duomenis
- visų paskyrų duomenys tikrinami prieš įrašant pakeitimus į failą
- po 3 nesėkmingų bandymų prisijungti, prisijungimas nutraukiamas

## Naudojamos C++ galimybės
Projektui realizuoti naudotos:
- struktūros (`struct`)
- vektoriai (`vector`)
- funkcijos
- ciklai (`for`,`while`)
- sąlygos (`if`,`switch`)
- failų skaitymas (`ifstream`)
- failų rašymas (`ofstream`)
- teksto formatavimas (`format`)
- tekstų apdorojimas (`getline`)
- paeiška tekstuose (`find`)
- duomenų saugojimas tekstiniuose failuose
