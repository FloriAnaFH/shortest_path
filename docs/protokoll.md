## Aufgabenstellung 
Ziel der Aufgabe ist die Implementierung eines Algorithmus zur Suche des kürzesten Pfades in einem gewichteten, ungerichteten Graphen, der ein öffentliches Verkehrsnetz darstellt.
Die Eingabe ist eine Textdatei, in der jede Zeile eine Linie beschreibt, wobei die Entfernung in Minuten zwischen Stationen auch dargestellt wird.
Das Programm wird mit drei Argumenten aufgerufen: dem Dateipfad, einer Startstation und einer Zielstation.
Als **Ausgabe** soll der kürzeste Weg übersichtlich dargestellt werden, inklusive der verwendeten Linien, notwendiger Umstiege und der Gesamtfahrzeit in Minuten.


## Der Algorithmus
Zur Suche des kürzesten Pfades wird der Algorithmus von Dijkstra verwendet.
Dabei wird ausgehend von der Startstation schrittweise der Graph erkundet. Jede Station bekommt eine Distanz zugewiesen, die anfangs "unendlich" ist, außer der Startstation, die den Wert 0 bekommt.
Als Datenstruktur wird eine Priority Queue verwendet, die immer die Station mit der kürzesten Fahrzeit als nächstes auswählt.
Für jede Nachbarstation wird geprüft, ob der neue Weg kürzer ist als der bisher bekannte. Wenn ja, wird die Distanz gespeichert und die Station erneut in die Queue eingefügt.
Damit am Ende der genaue Weg ausgegeben werden kann, merkt sich das Programm für jede Station, von wo sie erreicht wurde und mit welcher Linie. Der Pfad wird dann rückwärts zusammengebaut und umgedreht ausgegeben.

## O-Notation
| Operation | Komplexität | Begründung |
|---|---|---|
| Graph einlesen | O(V + E) | Jede Station und Kante wird einmal gelesen |
| Stationssuche (StationIndex) | O(1) | HashMap-Lookup |
| Station aus Queue holen | O(log V) | Heap muss sich neu sortieren |
| Kante prüfen & Queue aktualisieren | O(log V) | Neuer Eintrag in den Heap |
| Dijkstra gesamt | O((V + E) · log V) | V · log V + E · log V |
| Pfadrekonstruktion | O(V) | Einmal rückwärts durch die Vorgänger |
| **Gesamt** | **O((V + E) · log V)** | Dijkstra dominiert |

>Zusammenfassung: Die Gesamtkomplexität des Algorithmus ist O((V + E) · log V), wobei V die Anzahl der Stationen und E die Anzahl der Streckenabschnitte ist.
Jede Station wird einmal verarbeitet (V Operationen), jede Kante einmal geprüft (E Operationen). Da die Priority Queue intern als Min-Heap gespeichert ist, kostet jede dieser Operationen O(log V).

## Programm ausführen
### Kürzester Weg finden
> ./cmake-build-debug/shortest_path wien.txt "Leopoldau" "Reumannplatz"

Ausgabe:

Shortest path: 26 minutes:
Take U1 from "Leopoldau" to "Reumannplatz" (26 min, 17 segments)
---
### Zusammenfassung des Netzes
>./cmake-build-debug/shortest_path --summary wien.txt

Ausgabe:

Network loaded successfully

Routes: 35

Stations 450

Segments: 637

---
### Alle Stationen auflisten
>./cmake-build-debug/shortest_path --list-stations wien.txt


Ausgabe:

Absberggasse

Aderklaaer Strasse

Adolf-Unger-Gasse

Alaudagasse

Albertgasse

Alfred-Adler-Strasse

Alsegger Strasse

Alser Strasse

Alte Donau

...

---
### Stationen filtern (z.B. alle mit "platz")
>./cmake-build-debug/shortest_path --list-stations wien.txt platz

Ausgabe:

Arthaberplatz

Aumannplatz

Bauernfeldplatz

Brigittaplatz

...

---