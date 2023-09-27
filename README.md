# File Viewer Dokumentation

## Übersicht
Dieses Dokument stellt die Dokumentation für ein einfaches File viewer Programm, geschrieben in C. Das Programm lässt den Benutzer die Inhalte einer Datei in drei Formaten anzeigen: binär, hexadezimal und als Zeichenfolge. Für große Dateien gibt es eine Seitenfunktion.

## Inhalt
1. [Einleitung](#Einleitung)
2. [Funktionalität](#Funktionalität)
3. [Dependencies](#dependencies)
4. [Nutzung](#Nutzung)
5. [Erklärung des Programms](#code-explanation)
6. [Error Handling](#error-handling)
7. [Speicher Management](#Speicher-management)
8. [Seitenfunktion](#pagination)
9. [Kompilierung](#Kompilierung)
10. [Fazit](#Fazit)

## Einleitung <a name="Einleitung"></a>
Der file viewer ist dazu gedacht den Inhalt einer Binärdatei in verschiedenen Formaten darzustellen. Ein Nutzer kann zwischen den Formaten binär, hexadezimal und Zeichenfolge wählen. Um große Dateien besser anzeigen und lesen zu können, gibt es im Terminal eine Seitenfunktion.

## Funktionalität <a name="Funktionalität"></a>
Das Programm führt die folgenden Hauptfunktionen aus:
- Fragt den Namen der Datei vom Nutzer ab
- Fragt das gewünschte Ausgabeformat (bin, hex oder out) ab
- Öffnet die gewünschte Datei im Lesemodus.
- Löscht den Terminalbildschirm
- Bestimmt die Terminalgröße, um eine Seiteneinteilung zu ermöglichen.
- Zeigt den Inhalt der Datei im gewählten Format an.

## Dependencies <a name="dependencies"></a>
Das Programm nutzt folgende Bibliotheken:
- `stdio.h`: Für Standart input/output Operationen
- `stdlib.h`: Für Speicher zuweisung und exit Funktionen
- `string.h`: Für die Änderung von Strings
- `sys/ioctl.h`: Für die Größenbestimmung des Terminals
- `unistd.h`: Für IOCTL und Datei zugriff
- `limits.h`: Für Pfad Limits

## Nutzung <a name="Nutzung"></a>
Gehe folgendermaßen vor, um den file viewer zu verwenden:
1. Kompiliere das Programm (siehe Abschnitt [Kompilierung](#Kompilierung))
2. Führe die kompilierte ausführbare Datei aus
3. Gib den Namen der Datei ein, die angezeigt werden soll
4. Wähle das gewünschte Format (bin, hex, oder out)
5. Das Programm löscht das Terminal und zeigt den Inhalt der Datei in dem gewählten Format an

## Erklärung des Programms <a name="code-explanation"></a>
Das Programm ist in mehrere Teile unterteilt, die im Folgenden kurz erläutert werden:
- Die Speicherzuweisung dient dazu, Platz für die Speicherung des Dateinamens und der Formatwahl zu schaffen
- Das Programm löscht den Terminalbildschirm, der Inhalt ist nicht mehr relevant
- Die Größe des Terminals wird mit IOCTL bestimmt
- Für eine benutzerfreundliche Anzeige ist eine Seitenfunktion implementiert
- Je nach gewähltem Format liest das Programm den Inhalt der Datei und zeigt ihn entsprechend an
- Der für die Wahl des Dateinamens und des Formats reservierte Speicher wird vor dem Beenden des Programms wieder freigegeben

## Error Handling <a name="error-handling"></a>
Für Folgende Szenarien ist ein Error Handling implementiert:
- Speicherzuweisung Error
- Dateiöffungs Error
- Terminalgröße (Bestimmung) Error
- Error des aktuellen Speicherpfads

## Speicher Management <a name="speicher-management"></a>
Das Programm weist Speicher für den Dateinamen und die Formatwahl mit `malloc` zu. Es gibt diesen Speicher vor dem Beenden auch mit `free` wieder frei, um Speicherverlust zu vermeiden.

## Seitenfunktion <a name="pagination"></a>
Das Programm verwendet eine Seitenfunktion, um den Inhalt der Datei in überschaubaren Abschnitten auf der Basis der Terminalgröße anzuzeigen. Dadurch wird verhindert, dass der Nutzer mit einer großen Datenmenge überwältigt wird.

## Kompilierung <a name="Kompilierung"></a>
Um das Programm zu kompilieren, können Sie einen C-Compiler wie `gcc` verwenden. Zum Beispiel:
```shell
gcc file_viewer.c -o file_viewer
```

## Fazit <a name="Fazit"></a>
Der file viewer bietet eine einfache, aber effektive Möglichkeit, den Inhalt von Binärdateien in verschiedenen Formaten anzuzeigen. Es sorgt für eine benutzerfreundliche Erfahrung, indem es eine Seitenfunktion und Fehlerbehandlung implementiert. Diese Dokumentation soll dabei helfen, das Programm zu verstehen und entsprechend effektiv zu nutzen.

