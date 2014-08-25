//HydroPony 25/10/14
//Building for Mega2560

//including ethernet library
#include <Ethernet.h>
#include <EthernetUdp.h> // adds UPD support
//Temp sensor code and tutorial  https://learn.adafruit.com/tmp36-temperature-sensor

//TMP36 Attached to Pin XX - this is for reading the temp in the fish pond
int tempSen1Pin = 0;

//Setting for network interface 
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// assign an IP address for the controller:
IPAddress ip(192, 168, 0, 88);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
// port for sending data
unsigned int localPort = 8888; 
// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // put your setup code here, to run once:
  
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
 
 /* exaple code for reciving udp message maybe.
 int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
 */
 
 
 /* example code for writing UDP packet 
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  
  Udp.write(ReplyBuffer);
  Udp.endPacket();
 */
 
}
