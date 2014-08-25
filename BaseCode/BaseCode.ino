//HydroPony 25/10/14
//Building for Mega2560

//Temp sensor code and tutorial  https://learn.adafruit.com/tmp36-temperature-sensor

//TMP36 Attached to Pin XX - this is for reading the temp in the fish pond
int tempSen1Pin = 0;


void setup() {
  // put your setup code here, to run once:
  
  //Start the serial interface (this will be removed once we've added the network shield)
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // test import
  
  //read the temp from the sensor on pin 15 we need to do this twice and discard the first reading see notes below ( from adafruit guide )
   int tempreading1 = analogRead(tempSen1Pin); 
 //  small pause  
 delay(10); //10ms delay
 //this is the reading we are going to keep
   int tempreading1 = analogRead(tempSen1Pin); 
   
/*Problems you may encounter with multiple sensors:
If, when adding more sensors, you find that the temperature is inconsistant, 
this indicates that the sensors are interfering with each other when switching
the analog reading circuit from one pin to the other. 
You can fix this by doing two delayed readings and tossing out the first one */
  
// converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
  
// now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset 
 Serial.print(temperatureC); Serial.println(" degrees C"); //to degrees ((voltage - 500mV) times 100)
  
 delay(1000);  // debug delay so we have time to read the serial feed
}
