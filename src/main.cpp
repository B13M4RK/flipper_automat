#include <Arduino.h>

// Startknopf
int startLED = 38;
int startBtn = 39;
bool gameWorks = false;


void setup() {
    // Startknopf
    pinMode(startLED, OUTPUT);
    pinMode(startBtn, INPUT_PULLUP);

    // Serial Monitor
    Serial.begin(9600);
}

void detectStartGame() {

    if (digitalRead(startBtn) == HIGH) {
        gameWorks = true;
        digitalWrite(38, HIGH);
    }
}

void loop() {

    detectStartGame();

}