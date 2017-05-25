# ct-task

Zadání:
Mějme tuto modelovou situaci: Ve volbách do Poslanecké sněmovny bychom rádi, během sčítání hlasů, prezentovali tři druhy informací:
•	Jaká je účast voličů
•	Které strany, a s jakými zisky, se dostanou nad 5% hranici
•	Porovnání zisků uživatelem zvolených stran s výsledkem z předchozích voleb

Průběžné výsledky hlasování se budou prezentovat ve formě lineární „relace“, kdy uživatel z předem vytvořeného playlistu postupně přechází od jednoho grafu k druhému, krok za krokem.
Data jsou uložena v SQL databázi. Stačí co nejjednodušší implementace tabulek.
Poznámky ke grafům:
1.	Účast
Zobrazení: pouze jedna hodnota – údaj v %, zaokrouhlený na 1 desetinné místo.
2.	Strany – zisky
Zobrazení: Názvy stran s příslušnými zisky. Zisky jsou seřazené sestupně až do hodnoty 5%, dále se nezobrazují. Zisky jsou zaokrouhleny na 2 desetinná místa.
Na jednu obrazovou stránku (která odpovídá jedné položce playlistu) se vejde maximálně šestice stran.
3.	Strany – porovnání
Zobrazení: Název zvolené strany a k ní dvě hodnoty – současný průběžný zisk a zisk z minulých voleb. Zisky jsou zaokrouhleny na 1 desetinné místo.
Na jednu obrazovou stránku se vejde pouze jedna volební strana a k ní dvě porovnávající hodnoty.

Úkol:
1.	Vytvořte program, který umožní uživateli sestavit playlist („relaci“) z těchto tří zadaných typů grafů, a to v libovolném pořadí a s libovolným opakováním.
2.	Stiskem klávesy Enter se zobrazí data k aktuálně zvolené položce playlistu, kurzor se následně posune na položku následující. To, jakou formou se budou data prezentovat (textově / graficky), je necháno na vás, lepší je samozřejmě graficky.
3.	Stiskem tlačítka „Aktualizovat data“ se přegeneruje vytvořený playlist podle aktuálních průběžných výsledků z databáze. (Za tímto účelem je vhodné vytvořit jednoduchý editor dat SQL databáze).
