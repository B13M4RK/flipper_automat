# Flipperautomat - Arduino Projekt

Dieses Projekt ist ein selbst gebauter Flipperautomat, der mit einem Arduino gesteuert wird. Der Automat erkennt Treffer über Sensoren, zählt Punkte und zeigt Animationen über LEDs an, besitze eine klare Spiel-Logik mit Zuständen (Start, Spiel läuft, Ball verloren, Game Over). Außerdem wird der höchste Punktestand, der erspielt wurde gespeichert.

## Hardware

- Arduino Mega
- Kabel
- Widerstände
- Powerbank
- Kupferstangen
- Servomotor
- Feder
- LEDs
- Stepmotor
- Holzkuglen
- LCD & Digit Display
- Knöpfe
- Fotowiderstände
- Holz

### Spielregeln

- Der Spieler startet das Spiel mit dem Startknopf.
- Jeder Sensor gibt 100 Punkte, wenn alle drei Taster vom Kasten, dann X.
- Bei 3 Bällen im Rad bekommt man 300 Punkte.
- Wenn der Ball einen der beiden unteren Sensoren auslöst, ist er weg und man bekommt ihn nicht mehr. Insgesamt kann man 3 Bälle haben. Danach ist das Spiel verloren.