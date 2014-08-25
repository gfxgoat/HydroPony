//HydroPony 25/10/14
//Building for Mega2560

//<<<<<<< HEAD
// --- Global Variables ---
const int countTemp = 4; // Only 3 sensors for starters, done this way to make it flexible in the loop below
int pinTemp [countTemp] = {A0,A1,A2,A3}; //pins for sensors
int sensorTemp [countTemp]; //temp sensor readings
int sensorTimer = 10; //ms
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
  
  Set message back to the server
  */

 
  
for (count=0;count=countTemp;count++) {
 Serial.print(sensorTemp[count]); Serial.println(" degrees C"); //to degrees ((voltage - 500mV) times 100)
}
 delay(100);  // debug delay so we have time to read the serial feed
 
// Below comment 5 Lines, unsure why as compiled be for moving broke with copy and pasting time for bed =(
// String webMessage; // This will be the message returned to the server with the current status
//Writing the UDP packet with our string for the web server to eat
//  Udp.beginPacket(targetServer, localPort );  
//  Udp.write(webMessage);
//  Udp.endPacket();
 
 
 // exaple code for reciving udp message maybe.
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
void checkTemp () {
  for (count=0;count=countTemp;count++) {
   sensorTemp[count] = analogRead(pinTemp[countTemp]);//first sensor read - dump this as per adafruit guide 
   delay(sensorTimer);
   sensorTemp[count] = ((analogRead(pinTemp[countTemp]) * 5) / 1024) * 100  ;//second sensor read - keep.  change to 3.3 for 3.3v system. Converting from 10 mv per degree wit 500 mV offset
  }
}
