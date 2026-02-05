#include <Arduino.h>
#include "SevSeg.h"
SevSeg sevseg;

// put function declarations here:
int myFunction(int, int);

int counter_display_1 = 2;
int counter_display_a = 14;
int counter_display_f = 15;
int counter_display_2 = 16;
int counter_display_3 = 17;
int counter_display_b = 18;
int counter_display_4 = 19;
int counter_display_g = 20;
int counter_display_c = 21;
int counter_display_p = 22;
int counter_display_d = 23;
int counter_display_e = 24;

void setup() {
  
  // Punkte sammeln oben
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  // 3x Punkte sammeln Kasten
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  // Ballzähler
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  // Nummer Punkteanzeige
  pinMode(counter_display_1, OUTPUT);

}

void loop() {
  
}
