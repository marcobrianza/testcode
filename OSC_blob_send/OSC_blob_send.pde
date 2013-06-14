
import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation, myRemoteLocationLocal, myRemoteLocationArduino;

void setup() {
  size(200, 200);
  oscP5 = new OscP5(this, 10000);

  myRemoteLocation = new NetAddress("192.168.1.3", 10000); 
  myRemoteLocationArduino = new NetAddress("192.168.1.3", 10000);
  myRemoteLocationLocal = new NetAddress("127.0.0.1", 10000);
}

void draw() {
  background(100, 0, 100);
}


void keyPressed() { // click the window to send the OSC message

  switch (key) {
  case 'i':
    send_RGB();
    break;
  case 'b':
    send_rgb_blob();
    break;  
  case 'A':
    myRemoteLocation=myRemoteLocationArduino;
    break;  
  case 'L':
    myRemoteLocation=myRemoteLocationLocal;
    break;
  }
} 


void send_rgb_blob() {
  byte[] bb;
  bb=new byte[3];

  bb[0]=81;
  bb[1]=82;
  bb[2]=83;

  OscMessage myMessage = new OscMessage("/rgb_b");
  myMessage.add(bb); 

  println("Outgoing Message:-------");
  myMessage.print(); 

  oscP5.send(myMessage, myRemoteLocation);
}



//--------------------------------------------------------------------------
void send_RGB() {
  OscMessage myMessage = new OscMessage("/rgb_i");

  myMessage.add(11); 
  myMessage.add(12);
  myMessage.add(13); 

  println("Outgoing Message:-------");
  myMessage.print(); 

  oscP5.send(myMessage, myRemoteLocation);
}




/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  print("### received an osc message.");
  theOscMessage.print();

  //this prints correctly only if a message is a blob
  byte[] bb;
  bb=new byte[3];
  bb = theOscMessage.get(0).blobValue();
  println(bb[0]);
  println(bb[1]);
  println(bb[2]);
}

