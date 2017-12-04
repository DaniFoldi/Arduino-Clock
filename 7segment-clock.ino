#include <SevSeg.h>
#include <Wire.h>
#include <DS3231.h>

#define DEBUG 0
//OPTIONAL SERIAL DEBUG MODE
//NOT RECOMMENDED, SLOWS DOWN DISPLAY UPDATES

const int button1_pin = 4;
const int button2_pin = 3;

const byte segA = 8;
const byte segB = 9;
const byte segC = 10;
const byte segD = 11;
const byte segE = 12;
const byte segF = 13;
const byte segG = 7;

const byte anode1 = A3;
const byte anode2 = A2;
const byte anode3 = A1;
const byte anode4 = A0;

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

RTCDateTime dt;

int lastCheck = 0;

void setup() {
  if (DEBUG) {
    Serial.begin(19200);
    while (!Serial) {}
  }
  clock.begin();

  byte segment_array[] = {segA, segB, segC, segD, segE, segF, segG, 2};
  byte digit_array[] = {anode1, anode2, anode3, anode4};
  
  sevseg.begin((byte)COMMON_CATHODE, (byte)4, digit_array, segment_array, true, false, true);

  clock.setDateTime(__DATE__, __TIME__);
}

void loop() {
  //only check for time once a second
  //accurate, but a higher FPS can be achieved
  if (millis() - lastCheck > 1000) {
    dt = clock.getDateTime();
    lastCheck = millis();  
  }
  //check for setup buttons
  //get time
  int hour = dt.hour;
  int minute = dt.minute;
  //update brightness based on time
  if (hour >= 22 || hour <= 7) {
    sevseg.setBrightness(60);
  } else {
    sevseg.setBrightness(90);
  }
  //display time
  if (DEBUG) {
    Serial.print(hour);
    Serial.print(" ");
    Serial.println(minute);
  }
  sevseg.setNumber(100 * hour + minute, 0);
  sevseg.refreshDisplay();
}
