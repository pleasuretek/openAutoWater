/*
Soil moisture based irrigation controller. 
Device will turn on a pump for a single water cycle 
when it senses the soil is dry.
Moisture sensor also acts as a ground when actively taking a reading (think faraday cage for your rhizosphere)

Parts list:
-Arduino
-Relay (I use a solid state relay rated for 20A @120v and switches with 3v dc)
-Moisture sensor - SEN0114 from DFRobot 
-power cable
-plug recepticle

Soil Mediums
Mother Earth Coco - water at 420. (no perlite) it reads ~790 when wet and 420 when dry enough to water
TGA organic  - water at 333 (dense stuff)
Ready Gro  - water at 400 (light coco perlite mix)

Created by: Travis McCann 2014
*/

#define DEBUG true
//How often we take a reading of the soil
#define SLEEPTIME 3600000 //@ 6min to debug!!  3600000 = 60 minutes
//how long the pump runs to water
#define CYCLETIME 480000 //480000 = 8 minutes water cycle
#define MTHRESH 420  //threshold for how dry medium gets before watering

int mSamp       = 0;   //sample global variable
//pins
int moisture01  = 0;   //moisture sensor on pin Analog0 
int moistureVcc = 2;   //moisture sensor Vcc on pin digital2 
int relayPin    = 3;   //relay to turn on sump on pin digital3
int greenLED    = 13;   //water indicator on pin 13


void setup() {
  pinMode(moistureVcc, OUTPUT);
  pinMode(relayPin, OUTPUT);
  if (DEBUG) {
    Serial.begin(9600);
  }
}

void loop() {
  digitalWrite(moistureVcc, HIGH);  //turn on power to sensor
  delay(10);
  mSamp = analogRead(moisture01);  //take reading from sensor
  digitalWrite(moistureVcc, LOW);  //turn off power to sensor to prevent constant voltage to soil
  if (DEBUG) {
    Serial.print("sample: ");
    Serial.println(mSamp);
  }
  if(mSamp < MTHRESH) {
    if (DEBUG) {
      Serial.println("about to start water cycle");
    }
    waterCycle();
  }
  delay(SLEEPTIME);
}

void waterCycle() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(relayPin, HIGH);
  delay(CYCLETIME);  //keep relay on for this long
  digitalWrite(relayPin, LOW);
  digitalWrite(greenLED, LOW);
}


