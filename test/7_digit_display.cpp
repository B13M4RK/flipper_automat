#include "SevSeg.h"
#include <Arduino.h>

SevSeg sevseg;

void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
}

void loop() {
    sevseg.setNumber(1234, 2);
    sevseg.refreshDisplay();
    sevseg.setBrightness(90);
}