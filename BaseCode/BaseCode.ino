//HydroPony 25/10/14
//Building for Mega2560

// --- Global Variables ---
int countTemp = 3; // Only 3 sensors for starters, done this way to make it flexible in the loop below
int pinTemp |countTemp| = {15,16,17,18}; //pins for sensors
int sensorTemp |countTemp|; //temp sensor readings
int sensorTimer = 10; //ms
int count = 0;

//Temp sensor code and tutorial  https://learn.adafruit.com/tmp36-temperature-sensor

void setup() {
  //Start the serial interface (this will be removed once we've added the network shield)
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  --- Check ---
  Check Pumps
  Check Overflow sensors
  Check PH sensors
  Check ??? sensors
  */
  checkTemp();
  /*
  
  --- Process ---
  
  */
  

 Serial.print(temperatureC); Serial.println(" degrees C"); //to degrees ((voltage - 500mV) times 100)
  
 delay(1000);  // debug delay so we have time to read the serial feed
}

void checkTemp () {
  for (count=0;count=countTemp;count++) {
   sensorTemp|count| = analogRead(pinTemp|countTemp|);//first sensor read - dump this as per adafruit guide 
   delay(sensorTimer);
   sensorTemp|count| = ((analogRead(pinTemp|countTemp|) * 5) / 1024) * 100  ;//second sensor read - keep.  change to 3.3 for 3.3v system. Converting from 10 mv per degree wit 500 mV offset
  }
