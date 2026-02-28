#include <Arduino.h>

// Startknopf
int startLED = 38;
int startBtn = 39;
bool gameWorks = false;

// Ball rolls over
int fotowiderstandA6 = A6;
int valueA6;
bool ballWasOnA6 = false;
int fotowiderstandA14 = A14;
int valueA14;
int fotowiderstandA15 = A15;
int valueA15;

// Counter
long counter = 0;

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
    // Serial.print("A6: ");
    // Serial.println(valueA6);

    if (valueA6 <= 10 && !ballWasOnA6) {
        ballWasOnA6 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);

    } else if (valueA6 >= 15) {
        ballWasOnA6 = false;
    }
 
}

void refreshDisplays() {
    // LCD DISPLAY INITIALIZE
}

void loop() {

    detectStartGame();
    detectBallOver();
    refreshDisplays();
}