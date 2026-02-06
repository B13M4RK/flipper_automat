// =============== LIBRARIES ===============

#include <Arduino.h>

// Stepper Motor
#include "Stepper.h"
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

int SPU = 2048;

int counter;
int ballCounter;
int gameWorks;
int SchwelleDunkelheit = XX; // Helligkeit, übeprüfen wenn angeschlossen

int ballInWheel = 0;
int turnWheel = false;
int wheelSteps = 0;

int BallWasOnA1 = false;

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

  return counter;
};

int detectRollOver() {
  // --------------- GETTING POINTS ---------------

  // links
  if ((analogRead(A1) <= SchwelleDunkelheit) && !BallWasOnA1) {
    digitalWrite(13, HIGH);
    counter += 100;
    BallWasOnA1 = true;
  } else if (analogRead(A1) >= SchwelleDunkelheit) {
    BallWasOnA1 = false;
  }
  
  
  if (analogRead(A2) <= SchwelleDunkelheit) {
    counter += 100;
    digitalWrite(12, HIGH);
  }
  // rechts
  if (analogRead(A5) <= SchwelleDunkelheit) {
    counter += 100;
    digitalWrite(39, HIGH);
  }
  if (analogRead(A6) <= SchwelleDunkelheit) {
    counter += 100;
    digitalWrite(38, HIGH);
  }
  // kasten
  if (digitalRead(11) == HIGH) {
    counter += 100;
    digitalWrite(6, HIGH);
  }
  if (digitalRead(10) == HIGH) {
    counter += 100;
    digitalWrite(7, HIGH);
  }
  if (digitalRead(9) == HIGH) {
    counter += 100;
    digitalWrite(8, HIGH);
  }
  // analogRead für Drehrad + Motor
  if (analogRead(A7) == HIGH) {
    counter += 100;
    digitalWrite(34, HIGH);
  }

  if (analogRead(A8) == HIGH) {
    counter += 100;
    digitalWrite(35, HIGH);
    int LED35Time = millis();
    ballInWheel++;
    if (ballInWheel == 3) {
      turnWheel = true;
      ballInWheel = 0;
      counter += 20;
    }
  }
  if (turnWheel == true && (wheelSteps == 3 / 4 * 2048)) {
    wheelSteps += 20;
    Motor.step(20);
  } else {
    wheelSteps = 0;
    turnWheel = false;
  }

  if (analogRead(A9) == HIGH) {
    counter += 100;
    digitalWrite(36, HIGH);
  }

  // Variable, wie lang die LED an ist, ev variable auslesen in loop

  // --------------- BALL LOST ---------------
  if ((analogRead(A3) < SchwelleDunkelheit) || (analogRead(A4) < SchwelleDunkelheit)) {
    ballCounter--;
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

  return counter, ballCounter;
}

int endGame() {
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
