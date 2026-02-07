// =============== LIBRARIES ===============

#include <Arduino.h>

// Stepper Motor
#include "Stepper.h"
int SPU = 2048;
Stepper Motor(SPU, 33, 32, 31, 30); // IN 1, 2, 3, 4

// LCD Display
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

// digit display
#include "SevSeg.h"
SevSeg sevseg;

// =============== Global Variables ===============

int counter_display_1 = 2;
int counter_display_2 = 16;
int counter_display_3 = 17;
int counter_display_4 = 19;

int counter_display_a = 14;
int counter_display_b = 18;
int counter_display_c = 23;
int counter_display_d = 25;
int counter_display_e = 26;
int counter_display_f = 15;
int counter_display_g = 22;
int counter_display_p = 24;

int counter;
int ballCounter;
bool gameWorks;
int SchwelleDunkelheit = XX; // Helligkeit, übeprüfen wenn angeschlossen

int ballInWheel = 0;
bool turnWheel = false;
int wheelSteps = 0;

bool BallWasOnA1 = false;
bool BallWasOnA2 = false;
bool BallWasOnA3 = false;
bool BallWasOnA4 = false;
bool BallWasOnA5 = false;
bool BallWasOnA6 = false;
bool BallWasOnA7 = false;
bool BallWasOnA8 = false;
bool BallWasOnA9 = false;

bool BallWasOnD9 = false;
bool BallWasOnD10 = false;
bool BallWasOnD11 = false;

// =============== FUNCTIONS ===============

int startGame() {
    gameWorks = true;
    counter = 0;

    sevseg.setNumber(counter);

    lcd.setCursor(0, 0);
    lcd.print("Game soon starts...");

    ballCounter = 3;
    for (int pin = 3; pin <= 5; pin++) {
        digitalWrite(pin, HIGH);
    }
};

void detectRollOver() {
    // --------------- GETTING POINTS ---------------

    // LINKS
    int sensorValueA1 = analogRead(A1);
    if ((sensorValueA1 <= SchwelleDunkelheit) && !BallWasOnA1) {
        counter += 100;
        digitalWrite(13, HIGH);
        BallWasOnA1 = true;
    } else if (sensorValueA1 >= SchwelleDunkelheit) {
        BallWasOnA1 = false;
    }

    int sensorValueA2 = analogRead(A2);
    if (sensorValueA2 <= SchwelleDunkelheit && !BallWasOnA2) {
        counter += 100;
        digitalWrite(12, HIGH);
        BallWasOnA2 = true;
    } else if (sensorValueA2 >= SchwelleDunkelheit) {
        BallWasOnA2 = false;
    }

    // RECHTS
    int sensorValueA5 = analogRead(A5);
    if (sensorValueA5 <= SchwelleDunkelheit && !BallWasOnA5) {
        counter += 100;
        digitalWrite(39, HIGH);
        BallWasOnA5 = true;
    } else if (sensorValueA5 >= SchwelleDunkelheit) {
        BallWasOnA5 = false;
    }
    int sensorValueA6 = analogRead(A6);
    if (sensorValueA6 <= SchwelleDunkelheit && !BallWasOnA6) {
        counter += 100;
        digitalWrite(38, HIGH);
        BallWasOnA6 = true;
    } else if (sensorValueA6 >= SchwelleDunkelheit) {
        BallWasOnA6 = false;
    }

    // KASTEN
    int sensorValueD11 = digitalRead(11);
    if (sensorValueD11 == HIGH && !BallWasOnD11) {
        counter += 100;
        digitalWrite(6, HIGH);
        BallWasOnD11 = true;
    } else if (sensorValueD11 == LOW) {
        BallWasOnD11 = false;
    }

    int sensorValueD10 = digitalRead(10);
    if (sensorValueD10 == HIGH && !BallWasOnD10) {
        counter += 100;
        digitalWrite(7, HIGH);
        BallWasOnD10 = true;
    } else if (sensorValueD10 == LOW) {
        BallWasOnD10 = false;
    }

    int sensorValueD9 = digitalRead(9);
    if (sensorValueD9 == HIGH && !BallWasOnD9) {
        counter += 100;
        digitalWrite(8, HIGH);
        BallWasOnD9 = true;
    } else if (sensorValueD9 == LOW) {
        BallWasOnD9 = false;
    }

    // analogRead für Drehrad + Motor
    int sensorValueA7 = analogRead(A7);
    if (sensorValueA7 <= SchwelleDunkelheit && !BallWasOnA7) {
        counter += 100;
        digitalWrite(34, HIGH);
        BallWasOnA7 = true;
    } else if (sensorValueA7 >= SchwelleDunkelheit) {
        BallWasOnA7 = false;
    }

    int sensorValueA8 = analogRead(A8);
    if (sensorValueA8 <= SchwelleDunkelheit && !BallWasOnA8) {
        counter += 100;
        digitalWrite(35, HIGH);
        BallWasOnA8 = true;

        ballInWheel++;
        if (ballInWheel == 3) {
            turnWheel = true;
            ballInWheel = 0;
            counter += 20;
        }
    } else if (sensorValueA8 >= SchwelleDunkelheit) {
        BallWasOnA8 = false;
    }
    if ((turnWheel == true) && (wheelSteps <= (3 * 2048) / 4)) {
        wheelSteps += 20;
        Motor.step(20);
    } else {
        wheelSteps = 0;
        turnWheel = false;
    }

    int sensorValueA9 = analogRead(A9);
    if (sensorValueA9 <= SchwelleDunkelheit && !BallWasOnA9) {
        counter += 100;
        digitalWrite(36, HIGH);
        BallWasOnA9 = true;
    } else if (sensorValueA9 >= SchwelleDunkelheit) {
        BallWasOnA9 = false;
    }

    // Variable, wie lang die LED an ist, ev variable auslesen in loop

    // --------------- BALL LOST ---------------
    int sensorValueA3 = analogRead(A3);
    int sensorValueA4 = analogRead(A4);

    if ((sensorValueA3 <= SchwelleDunkelheit && !BallWasOnA3)) {
        ballCounter--;
        BallWasOnA3 = true;
    } else if (sensorValueA3 >= SchwelleDunkelheit) {
        BallWasOnA3 = false;
    }
    if (sensorValueA4 <= SchwelleDunkelheit && !BallWasOnA4) {
        ballCounter--;
        BallWasOnA4 = true;
    } else if (sensorValueA4 >= SchwelleDunkelheit) {
        BallWasOnA4 = false;
    }

    if (ballCounter == 2) {
        digitalWrite(3, LOW);
    } else if (ballCounter == 1) {
        digitalWrite(4, LOW);
    }
    if (ballCounter == 0) {
        digitalWrite(5, LOW);
        endGame();
    }
}

void endGame() {
    gameWorks = false;
    counter = 0;

    lcd.clear();
    lcd.print("You lost");

    delay(5000);
    lcd.clear();
    lcd.print("Put in 1€");
}

void setup() {
    // -------------BALL-------------
    // Ballausgabe
    pinMode(40, OUTPUT);
    // Ball weg
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    // Ballzähler
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);

    // -------------Punkte-------------
    // links
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    // rechts
    pinMode(38, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);
    // Bei Kasten
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    // Bei Drehrad
    Motor.setSpeed(5);
    pinMode(34, OUTPUT);
    pinMode(35, OUTPUT);
    pinMode(37, OUTPUT);
    pinMode(A7, INPUT);
    pinMode(A8, INPUT);
    pinMode(A9, INPUT);
    // Nummer Punkteanzeige
    byte numDigits = 4;
    byte digitPins[] = {counter_display_1, counter_display_2, counter_display_3, counter_display_4};
    byte segmentPins[] = {counter_display_a, counter_display_b, counter_display_c, counter_display_d, counter_display_e, counter_display_f, counter_display_g, counter_display_p};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); // is it common cathode or anode?
    sevseg.setBrightness(90);

    // -------------Andere-------------
    gameWorks = false;
    // Startknopf
    pinMode(27, INPUT);
    // Münzeinwurf
    pinMode(A13, INPUT);
    // Best Player Anzeige (LCD)
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Put in 1€");
}

// =============== LOOP ===============

void loop() {
    if ((digitalRead(27) == HIGH) && (gameWorks == false) /*&& Münzeinwurf*/) {
        startGame();
    }

    detectRollOver();

    sevseg.setNumber(counter);
    sevseg.refreshDisplay();
}
