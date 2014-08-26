//HydroPony 25/10/14
//Building for Mega2560

//<<<<<<< HEAD
// --- Global Variables ---
const int countTemp = 4; // Only 3 sensors for starters, done this way to make it flexible in the loop below
int pinTemp [countTemp] = {A0,A1,A2,A3}; //pins for sensors
int sensorTemp [countTemp]; //temp sensor readings
int sensorTimer = 10; //ms, used to slow down the time between reading to allow it to normalise
int count = 0;

//Temp sensor code and tutorial  https://learn.adafruit.com/tmp36-temperature-sensor
//=======
//including ethernet library
#include <Ethernet.h>
#include <SPI.h>
#include <EthernetUdp.h> // adds UPD support
//Temp sensor code and tutorial  https://learn.adafruit.com/tmp36-temperature-sensor

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back
//Setting for network interface 
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// assign an IP address for the controller:
IPAddress ip(192, 168, 0, 88);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
// traget server address
IPAddress targetServer(192, 168, 0, 89);
// port for sending data
unsigned int localPort = 8888; 
// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
//>>>>>>> origin/master

void setup() {
  //Start the serial interface (this will be removed once we've added the network shield)
  Serial.begin(9600);
  // start ethernet
 Ethernet.begin(mac, ip);
 Udp.begin(localPort);
  // delay for ethernet to come up
 delay(1000);
}

void loop() {
  

// Check all sensors
 
 // --- Check ---
//  Check Pumps
//  Check Overflow sensors
//  Check PH sensors
//  Check ??? sensors
//  Get Flow reading ...
String currentTemps = checkTemp(); //checkTemps

    // below 4 lines to be removed ones network reliable 
for (count=0;count=countTemp;count++) {
 Serial.print(sensorTemp[count]); Serial.println(" degrees C"); //to degrees ((voltage - 500mV) times 100)
}
delay(1000);  // debug delay so we have time to read the serial feed


//  --- Process Checks---

//Construct message to send message back to the server // add all the stings together
String udpMessage = "test"; //String to hold our message //udpMessage = String(CheckPumps_result + CheckOverflow_result + etc..);

//future break the messageout to sub and just send the messages ( this can be called if there is an alert also )

// need to set the size of our messageBuffer
//char  messageBuffer[udpMessage.length()+1] = udpMessage; // it would appear our first approach is not possible, so we'll have to fix our message length and extend as necessary "BaseCode:78: error: variable-sized object 'messageBuffer' may not be initialized"

char messageBuffer[50]; // Setting buffer length to 50 Chr. we'll need to increase this as we make longer messages. (50 char is quite long ( not sure how big the packet buffer is)
udpMessage.toCharArray(messageBuffer,sizeof(messageBuffer) -1);//udpMessage convert to char array, inset into messageBuffer, with the length of MessageBuffer -1 (Strings have a null Chr at the end of them we'll remove this (may have got this wrong may need to do + 1 to allow for it only one way to find out)

// String webMessage; // This will be the message returned to the server with the current status
// Writing the UDP packet with our string for the web server to eat
  Udp.beginPacket(targetServer, localPort );  
  Udp.write(messageBuffer);
  Udp.endPacket(); //sent BOOM 
 
 
 // exaple code for reciving udp message to change settings i suppect we'd use this for changing things ....
 // at the moment the Pony is very much a passive device just reads data, it does no controlling - in the future maybe control heater and pumps for the sump / valves ...
int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.print("Contents: ");
    Serial.println(packetBuffer);
   // Ok we got a incoming message do somthing with it
   
  // brake down the message and then call somthing to happen 
  }
}

// Subs start - 
 
String checkTemp () {
  for (count=0;count=countTemp;count++) { //this does not make sense to me ... this only dies if count = a sensor reading ? 
                                          //this should be something like count = 4 reading then we add [1+2+3] from the array and divide by 3 to get an average 
                                          //( dumping our bogus first reading 0 ) ? or should i go to bed ..
   sensorTemp[count] = analogRead(pinTemp[countTemp]);//first sensor read - dump this as per adafruit guide 
   delay(sensorTimer);
   sensorTemp[count] = ((analogRead(pinTemp[countTemp]) * 5) / 1024) * 100  ;//second sensor read - keep.  change to 3.3 for 3.3v system. Converting from 10 mv per degree with 500 mV offset
  }
  
  String _string = "ALL of the values";
  return _string;
}



//boolean  Check Pumps
//return 0 ok 1 warning 
//boolean Check Overflow sensors
//return 0 ok 1 warning 
//String  Check PH sensors
// return _StingOfSensorReadings
//String  Check ??? sensors
 



