

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <SPI.h>



//network stuff------------------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 3); //the Arduino's IP
const byte MAX_MSG_SIZE=64;  // 64 sould be ok
byte packetBuffer[MAX_MSG_SIZE];  //buffer to hold incoming udp packet,
EthernetUDP Udp;
const unsigned int inPort = 10000;
const unsigned int outPort = 11000;
  
// ----------------------------------------------

void setup(){   

  Ethernet.begin(mac,ip);
  Udp.begin(inPort);
  
  Serial.begin(115200);
  Serial.println("Hello");
}
  
// - ---------------------------------------------  
  
void loop(){
  OSCMessage messageIN;
   byte rgb[3]={ 0x01, 0x02, 0x03};
   
  int s = Udp.parsePacket();
 
  if(s)
  {
    Udp.read(packetBuffer,s);
    messageIN.fill(packetBuffer,s);
    
    Serial.print("UDP packet size= ");
    Serial.println(s);
    
    for( int x=0; x<s; x++){
     Serial.print((packetBuffer[x])); 
     Serial.print(" "); 
    }
    Serial.println();
    
    
        if(!messageIN.hasError())
        {
         if( messageIN.fullMatch("/rgb_b"))           // rgb values as blob
         {
          int n;
   
          n=messageIN.getBlob(0,rgb,3);
          Serial.println("received rgb_b ");
          Serial.print("blob size=");
          Serial.println(n);
          Serial.println(rgb[0]);
          Serial.println(rgb[1]);
          Serial.println(rgb[2]);  
          }

          if( messageIN.fullMatch("/rgb_i"))            // rgb values as 3 integers
         {
   
          rgb[0]=byte(messageIN.getInt(0));
          rgb[1]=byte(messageIN.getInt(1));
          rgb[2]=byte(messageIN.getInt(2));
          
          Serial.println("received rgb_i ");
          Serial.println(rgb[0]);
          Serial.println(rgb[1]);
          Serial.println(rgb[2]);  
          } 
             
      }
  }
} 

 
 
 
