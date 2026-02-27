#include <Arduino.h>

// Startknopf
int startLED = 38;
int startBtn = 39;
bool gameWorks = false;

// Ball rolls over
int fotowiderstandA6 = A6;
int valueA6;
int fotowiderstandA14 = A14;
int valueA14;
int fotowiderstandA15 = A15;
int valueA15;

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
        digitalWrite(startLED, HIGH);
    }
}

void detectBallOver() {

    valueA6 = analogRead(fotowiderstandA6);
    valueA14 = analogRead(fotowiderstandA14);
    valueA15 = analogRead(fotowiderstandA15);
    Serial.print("A6: ");
    Serial.println(valueA6);
}

void loop() {

    detectStartGame();
    detectBallOver();
}