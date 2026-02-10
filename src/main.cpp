// test if repository works

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

int LEDTime = 2000;

bool LEDOnA1 = false;
unsigned long LEDTimeA1;
bool LEDOnA2 = false;
unsigned long LEDTimeA2;
bool LEDOnA3 = false;
unsigned long LEDTimeA3;
bool LEDOnA4 = false;
unsigned long LEDTimeA4;
bool LEDOnA5 = false;
unsigned long LEDTimeA5;
bool LEDOnA6 = false;
unsigned long LEDTimeA6;
bool LEDOnA7 = false;
unsigned long LEDTimeA7;
bool LEDOnA8 = false;
unsigned long LEDTimeA8;
bool LEDOnA9 = false;
unsigned long LEDTimeA9;

bool LEDOnD9 = false;
unsigned long LEDTimeD9;
bool LEDOnD10 = false;
unsigned long LEDTimeD10;
bool LEDOnD11 = false;
unsigned long LEDTimeD11;

unsigned long highscore = 0;

bool showHighscore = false;
bool wasOnHighscore = false;
bool wasOnEuro = false;
unsigned long highscoreTime;
unsigned long putIn1€Time;

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
        // edge detection
        counter += 100;
        BallWasOnA1 = true;

        // time detection
        LEDOnA1 = true;
        LEDTimeA1 = millis();

    } else if (sensorValueA1 >= SchwelleDunkelheit) {
        // intervall stops
        BallWasOnA1 = false;
    }

    int sensorValueA2 = analogRead(A2);
    if (sensorValueA2 <= SchwelleDunkelheit && !BallWasOnA2) {
        // edge detection
        counter += 100;
        BallWasOnA2 = true;

        // time detection
        LEDOnA2 = true;
        LEDTimeA2 = millis();

    } else if (sensorValueA2 >= SchwelleDunkelheit) {
        // intervall stops
        BallWasOnA2 = false;
    }

    // RECHTS
    int sensorValueA5 = analogRead(A5);
    if (sensorValueA5 <= SchwelleDunkelheit && !BallWasOnA5) {
        // edge detection
        counter += 100;
        BallWasOnA5 = true;

        // time detection
        LEDOnA5 = true;
        LEDTimeA5 = millis();

    } else if (sensorValueA5 >= SchwelleDunkelheit) {
        BallWasOnA5 = false;
    }

    int sensorValueA6 = analogRead(A6);
    if (sensorValueA6 <= SchwelleDunkelheit && !BallWasOnA6) {
        // edge detection
        counter += 100;
        BallWasOnA6 = true;

        // time detection
        LEDOnA6 = true;
        LEDTimeA6 = millis();

    } else if (sensorValueA6 >= SchwelleDunkelheit) {
        BallWasOnA6 = false;
    }

    // KASTEN
    int sensorValueD9 = digitalRead(9);
    if (sensorValueD9 == HIGH && !BallWasOnD9) {
        // edge detection
        counter += 100;
        BallWasOnD9 = true;

        // time detection
        LEDOnD9 = true;
        LEDTimeD9 = millis();

    }

    int sensorValueD10 = digitalRead(10);
    if (sensorValueD10 == HIGH && !BallWasOnD10) {
        // edge detection
        counter += 100;
        BallWasOnD10 = true;

        // time detection
        LEDOnD10 = true;
        LEDTimeD10 = millis();

    }

    int sensorValueD11 = digitalRead(11);
    if (sensorValueD11 == HIGH && !BallWasOnD11) {
        // edge detection
        counter += 100;
        BallWasOnD11 = true;

        // time detection
        LEDOnD11 = true;
        LEDTimeD11 = millis();

    }

    if (BallWasOnD9 && BallWasOnD10 && BallWasOnD11) {
        counter += 200;
        BallWasOnD9 = false;
        BallWasOnD10 = false;
        BallWasOnD11 = false;

    }
    
    // DREHRAD UND SENSOREN DARÜBER
    int sensorValueA7 = analogRead(A7);
    if (sensorValueA7 <= SchwelleDunkelheit && !BallWasOnA7) {

        // edge detection
        counter += 100;
        BallWasOnA7 = true;

        // time detection
        LEDOnA7 = true;
        LEDTimeA7 = millis();

    } else if (sensorValueA7 >= SchwelleDunkelheit) {
        BallWasOnA7 = false;
    }

    int sensorValueA8 = analogRead(A8);
    if (sensorValueA8 <= SchwelleDunkelheit && !BallWasOnA8) {

        // edge detection
        counter += 100;
        BallWasOnA8 = true;

        // time detection
        LEDOnA8 = true;
        LEDTimeA8 = millis();

        // spin wheel detection
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
        counter += 300;
    }

    int sensorValueA9 = analogRead(A9);
    if (sensorValueA9 <= SchwelleDunkelheit && !BallWasOnA9) {

        // edge detection
        counter += 100;
        BallWasOnA9 = true;

        // time detection
        LEDOnA9 = true;
        LEDTimeA9 = millis();

    } else if (sensorValueA9 >= SchwelleDunkelheit) {
        BallWasOnA9 = false;
    }

    // --------------- BALL LOST ---------------
    int sensorValueA3 = analogRead(A3);
    int sensorValueA4 = analogRead(A4);

    if ((sensorValueA3 <= SchwelleDunkelheit && !BallWasOnA3)) {

        // edge detection
        ballCounter--;
        BallWasOnA3 = true;

    } else if (sensorValueA3 >= SchwelleDunkelheit) {
        BallWasOnA3 = false;
    }
    if (sensorValueA4 <= SchwelleDunkelheit && !BallWasOnA4) {

        // edge detection
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

void handleLEDs() {
    if (LEDOnA1 == true) {
        digitalWrite(13, HIGH);
        if (millis() - LEDTimeA1 >= LEDTime) {
            digitalWrite(13, LOW);
            LEDOnA1 = false;
        }
    }
    if (LEDOnA2 == true) {
        digitalWrite(12, HIGH);
        if (millis() - LEDTimeA2 >= LEDTime) {
            digitalWrite(12, LOW);
            LEDOnA2 = false;
        }
    }
    if (LEDOnA5 == true) {
        digitalWrite(39, HIGH);
        if (millis() - LEDTimeA5 >= LEDTime) {
            digitalWrite(39, LOW);
            LEDOnA5 = false;
        }
    }
    if (LEDOnA6 == true) {
        digitalWrite(38, HIGH);
        if (millis() - LEDTimeA6 >= LEDTime) {
            digitalWrite(38, LOW);
            LEDOnA6 = false;
        }
    }
    if (LEDOnA7 == true) {
        digitalWrite(34, HIGH);
        if (millis() - LEDTimeA7 >= LEDTime) {
            digitalWrite(34, LOW);
            LEDOnA7 = false;
        }
    }
    if (LEDOnA8 == true) {
        digitalWrite(35, HIGH);
        if (millis() - LEDTimeA8 >= LEDTime) {
            digitalWrite(35, LOW);
            LEDOnA8 = false;
        }
    }
    if (LEDOnA9 == true) {
        digitalWrite(36, HIGH);
        if (millis() - LEDTimeA9 >= LEDTime) {
            digitalWrite(36, LOW);
            LEDOnA9 = false;
        }
    }

    if (LEDOnD9 == true) {
        digitalWrite(8, HIGH);
        if (millis() - LEDTimeD9 >= LEDTime) {
            digitalWrite(8, LOW);
            LEDOnD9 = false;
        }
    }
    if (LEDOnD10 == true) {
        digitalWrite(7, HIGH);
        if (millis() - LEDTimeD10 >= LEDTime) {
            digitalWrite(7, LOW);
            LEDOnD10 = false;
        }
    }
    if (LEDOnD11 == true) {
        digitalWrite(6, HIGH);
        if (millis() - LEDTimeD11 >= LEDTime) {
            digitalWrite(6, LOW);
            LEDOnD11 = false;
        }
    }
}

void endGame() {

    if (counter > highscore) {
        highscore = counter;
    }

    gameWorks = false;
    counter = 0;

    lcd.clear();
    lcd.print("You lost");

    delay(5000);
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
    
}

void refreshDisplays() {

    if (!gameWorks && !showHighscore) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put in 1€");
        if (!wasOnEuro) {
            putIn1€Time = millis();
            wasOnEuro = true;
        }
        wasOnHighscore = false;
        
    } else if (!gameWorks && showHighscore) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Highscore:");
        lcd.setCursor(0, 1);
        lcd.print(highscore);
        if (!wasOnHighscore) {
            highscoreTime = millis();
            wasOnHighscore = true;
        }
        wasOnEuro = false;
    } else if (gameWorks) {
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("Good luck!");
    }

    if ((!showHighscore) && (millis() - putIn1€Time >= 3000)) {
        showHighscore = true;
        wasOnEuro = false;
    }
    if  ((showHighscore) && (millis() - highscoreTime >= 3000)) {
        showHighscore = false;
        wasOnHighscore = false;
    }


    sevseg.setNumber(counter);
    sevseg.refreshDisplay();
}

void detectStartGame() {

	if ((digitalRead(27) == HIGH) && (gameWorks == false) /*&& Münzeinwurf*/) {
        startGame();
}

// =============== LOOP ===============

void loop() {

	detectStartGame();

    detectRollOver();
    handleLEDs();

    refreshDisplays();
}
