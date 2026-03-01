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
int LEDA6 = 44;

int fotowiderstandA7 = A7;
int valueA7;
bool ballWasOnA7 = false;
int LEDA7 = 46;

int fotowiderstandA8 = A8;
int valueA8;
bool ballWasOnA8 = false;
int LEDA8 = 48;

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
    pinMode(LEDA7, OUTPUT);
    pinMode(LEDA8, OUTPUT);
}

void detectStartGame() {

    if (digitalRead(startBtn) == HIGH) {
        gameWorks = true;
        digitalWrite(startLED, HIGH);
    }
}

void detectBallOver() {

    valueA6 = analogRead(fotowiderstandA6);
    valueA7 = analogRead(fotowiderstandA7);
    valueA8 = analogRead(fotowiderstandA8);
    Serial.print("connected");
    Serial.println(valueA6);


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

    if (valueA7 <= 100 && !ballWasOnA7) {
        ballWasOnA7 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);
        digitalWrite(LEDA7, HIGH);

    } else if (valueA7 >= 110) {
        ballWasOnA7 = false;
        digitalWrite(LEDA7, LOW);
    }

    if (valueA8 <= 100 && !ballWasOnA8) {
        ballWasOnA8 = true;
        counter += 100;
        Serial.print("Counter: ");
        Serial.println(counter);
        digitalWrite(LEDA8, HIGH);

    } else if (valueA8 >= 110) {
        ballWasOnA8 = false;
        digitalWrite(LEDA8, LOW);
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