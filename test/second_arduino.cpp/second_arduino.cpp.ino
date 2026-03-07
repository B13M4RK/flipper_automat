// 7 digit display
#include "SevSeg.h"
SevSeg sevseg;

// arduino communication
String msg = "";

void setup() {
  // 7 digit display
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);

  // arduino communication
  Serial.begin(9600);
}
void loop() {

  // --- Counter vom Mega empfangen ---
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      long value = msg.toInt();
      sevseg.setNumber(value);
      msg = "";
    } else {
      msg += c;
    }
  }

  // --- Display aktualisieren ---
  sevseg.refreshDisplay();
}
