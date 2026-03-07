#include "SevSeg.h"
SevSeg sevseg;

char buffer[10];
byte index = 0;
int counter = 0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {               // Zahl vollständig
      buffer[index] = '\0';
      counter = atoi(buffer);      // in int umwandeln
      index = 0;                   // Puffer zurücksetzen
    } 
    else if (index < 9) {
      buffer[index++] = c;         // Zeichen sammeln
    }
  }

  sevseg.setNumber(counter);
  sevseg.refreshDisplay();         // läuft jetzt konstant
}
