#include <SevSeg.h>
#include <Wire.h>
#include <DS3231.h>

#define DEBUG 0

const int button1_pin = 4;
const int button2_pin = 3;

const int segA = 8;
const int segB = 9;
const int segC = 10;
const int segD = 11;
const int segE = 12;
const int segF = 13;
const int segG = 7;

const int anode1 = A3;
const int anode2 = A2;
const int anode3 = A1;
const int anode4 = A0;

bool button1_last_pressed = false;
bool button2_last_pressed = false;

/*
 * LIBRARIES NEEDED:
 * 
 * https://github.com/jarzebski/Arduino-DS3231
 * https://github.com/DeanIsMe/SevSeg
 * 
 */

DS3231 clock;
SevSeg sevseg;

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    while (!Serial) {}
  }
  clock.begin();
  sevseg.begin(COMMON_ANODE, 4, [anode1, anode2, anode3, anode4], [segA, segB, segC, segD, segE, segF, segG], true, false, false);

  clock.setDateTime(__DATE__, __TIME__);
}

void loop() {
  //check for setup buttons
  //get time
  
  //update brightness based on time
  //display time
  sevseg.refreshDisplay();
}
