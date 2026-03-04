#include <Arduino.h>

// LCD Display
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool pressStartIsShown = false;
bool goodLuckIsShown = false;

// Startknopf
int startLED = 22;
int startBtn = 23;
bool gameWorks = false;

// Ball rolls over
int fotowiderstandPins[10] = {A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
int valueA[10];
bool ballWasOnA[10] = {false};

int LEDA[10] = {44, 46, 48, 50, 52, 53, 51, 49, 47, 45};

// Counter
long counter = 0;

void setup() {
    // Startknopf
    pinMode(startLED, OUTPUT);
    pinMode(startBtn, INPUT_PULLUP);

    // Serial Monitor
    Serial.begin(9600);

    // LCD Display
    lcd.init();
    lcd.backlight();

    // LEDs Fotowiderstände
    for (int i = 0; i < 10; i++) {
        pinMode(LEDA[i], OUTPUT);
    }
    lcd.clear();
    lcd.print("Initialize");
    delay(1000);
}

void detectStartGame() {

    if (digitalRead(startBtn) == HIGH) {
        gameWorks = true;
        digitalWrite(startLED, HIGH);
    }
}

void detectBallOver() {

    for (int i = 0; i < 10; i++) {
        valueA[i] = analogRead(fotowiderstandPins[i]);
    }

    for (int i = 0; i < 10; i++) {
        if (valueA[i] <= 110 && !ballWasOnA[i]) {
            ballWasOnA[i] = true;
            counter += 100;

            Serial.println("Counter A" + String(i + 6) + ": " + String(counter));
            Serial.println("ValueA" + String(i + 6) + ": " + String(valueA[i]));

            digitalWrite(LEDA[i], HIGH);
        } else if (valueA[i] > 115) {
            ballWasOnA[i] = false;
            digitalWrite(LEDA[i], LOW);
        }
    }
    Serial.println(counter);
}

void refreshDisplays() {
    // LCD
    if (!gameWorks && !pressStartIsShown) {
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("Press Start");
        pressStartIsShown = true;
    }
    if (gameWorks && !goodLuckIsShown) {
        lcd.clear();
        lcd.print("Good Luck!");
        goodLuckIsShown = true;
    }
}

void loop() {

    detectStartGame();
    detectBallOver();
    refreshDisplays();
}