#include <Arduino.h>

// digit display
#include "SevSeg.h"
SevSeg sevseg;

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

// Stepper Motor
#include "Stepper.h"
int SPU = 2048;
Stepper Motor(SPU, 33, 32, 31, 30); // IN 1, 2, 3, 4

// LCD Display
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

int counter;
int balls;

// FUNCTIONS
int startGame()
{
  counter = 0;
  sevseg.refreshDisplay();
  sevseg.setNumber(counter);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Game soon starts...");
  for (int pin = 3; pin <= 5; pin++)
  {
    digitalWrite(pin, HIGH);
  }

  return counter;
};

int SchwelleDunkelheit = XX; // Helligkeit, übeprüfen wenn angeschlossen
int detectRollOver()
{
  // links
  if (A1 <= SchwelleDunkelheit)
  {
    counter += 100;
    digitalWrite(13, HIGH);
  }
  if (A2 <= SchwelleDunkelheit)
  {
    counter += 100;
    digitalWrite(12, HIGH);
  }
  // rechts
  if (A5 <= SchwelleDunkelheit)
  {
    counter += 100;
    digitalWrite(39, HIGH);
  }
  if (A6 <= SchwelleDunkelheit)
  {
    counter += 100;
    digitalWrite(38, HIGH);
  }
  // kasten
  if (digitalRead(11) == HIGH)
  {
    counter += 100;
    digitalWrite(8, HIGH);
  }
  if (digitalRead(11) == HIGH)
  {
    counter += 100;
    digitalWrite(7, HIGH);
  }
  if (digitalRead(11) == HIGH)
  {
    counter += 100;
    digitalWrite(6, HIGH);
  }

  // Variable für Zeit
}

void setup()
{
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
  // Startknopf
  pinMode(27, INPUT);
  // Münzeinwurf
  pinMode(A13, INPUT);
  // Best Player Anzeige (LCD)
  lcd.init();
  lcd.backlight();
}

void loop()
{
  if (digitalRead(27) == HIGH)
  {
    startGame();
  }

  detectRollOver();
}
