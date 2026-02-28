#include <Arduino.h>

// LCD Display
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool pressStartIsShown = false;
bool goodLuckIsShown = false;

// Startknopf
int startLED = 38;
int startBtn = 39;
bool gameWorks = false;

// Ball rolls over
int fotowiderstandA6 = A6;
int valueA6;
bool ballWasOnA6 = false;
int LEDA6 = 53;

int fotowiderstandA14 = A14;
int valueA14;
bool ballWasOnA14 = false;
int LEDA14 = 52;

int fotowiderstandA15 = A15;
int valueA15;
bool ballWasOnA15 = false;
int LEDA15 = 51;

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
    pinMode(LEDA6, OUTPUT);
    pinMode(LEDA14, OUTPUT);
    pinMode(LEDA15, OUTPUT);
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
    Serial.print("A14: ");
    Serial.println(valueA14);
    Serial.print("A15: ");
    Serial.println(valueA15);

    if (valueA6 <= 100 && !ballWasOnA6) {
        ballWasOnA6 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);
        digitalWrite(LEDA6, HIGH);

    } else if (valueA6 >= 110) {
        ballWasOnA6 = false;
        digitalWrite(LEDA6, LOW);
    }

    if (valueA14 <= 100 && !ballWasOnA14) {
        ballWasOnA14 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);
        digitalWrite(LEDA14, HIGH);

    } else if (valueA14 >= 110) {
        ballWasOnA14 = false;
        digitalWrite(LEDA14, LOW);
    }

    if (valueA15 <= 100 && !ballWasOnA15) {
        ballWasOnA15 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);
        digitalWrite(LEDA15, HIGH);

    } else if (valueA15 >= 110) {
        ballWasOnA15 = false;
        digitalWrite(LEDA15, LOW);
    }
}

void refreshDisplays() {
    if (!gameWorks && !pressStartIsShown) {
        lcd.setCursor(0, 0);
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