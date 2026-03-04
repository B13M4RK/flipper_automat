// UPLOAD>>C :\Users\pauld\.platformio\penv\Scripts\platformio.exe run - e uno-- target upload

#include "SevSeg.h"
#include <Arduino.h>

SevSeg sevseg;
int counter = 4567;

void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
}

void loop() {
    sevseg.setNumber(counter, 2);
    sevseg.refreshDisplay();
    sevseg.setBrightness(90);
}