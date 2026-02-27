#include <Arduino.h>

// Startknopf
int startLED = 38;
int startBtn = 39;
bool gameWorks = false;

// Ball rolls over
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
    valueA15 = analogRead(fotowiderstandA15);
    Serial.print("A15: ");
    Serial.println(valueA15);
}

void loop() {

    detectStartGame();
    detectBallOver();
}