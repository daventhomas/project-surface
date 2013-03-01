// Process TUIO 2d cursor events into Win8 HID Touch

#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0x90, 0xA2, 0xDA, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177);

unsigned int inPort = 3333;      // local port to listen on

//UDP communication
EthernetUDP Udp;

//a bundle for all the incoming messages
OSCBundle bundleIN(Udp);

#define MAX_X 32767
#define MAX_Y 32767

typedef struct 
{
    uint8_t TipSwitch;
    uint8_t ContactId; 
    int16_t  x; /**< Current absolute touch X position, as a signed 16-bit integer */
    int16_t  y; /**< Current absolute touch Y position, as a signed 16-bit integer */
    int16_t  ScanTime; 
    uint8_t ContactCount; 
} TouchReport;

#define MAX_TOUCH 10

typedef struct 
{
    int16_t  x; /**< Current absolute touch X position, as a signed 16-bit integer */
    int16_t  y; /**< Current absolute touch Y position, as a signed 16-bit integer */
    int16_t  ScanTime; 
    int touchId;
    boolean active;
} ActiveTouch;

ActiveTouch touch[MAX_TOUCH];
int activeTouch = 0;

void setup() 
{

  Serial.begin(115200);

  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);

  //Serial.println("TUIO Start Receive: ");    
}


void loop()
{
  //clear the incoming bundle
  bundleIN.clear();  
  //read the incoming messages
  bundleReceive();
}

int findTouchId(int id)
{
  int i = 0;
  boolean found = false;
  while (i < MAX_TOUCH && !found)
  {
    if (touch[i].touchId == id)
    {
      found = true;
      break;
    }
    i++;
  }
  if (found)
    return i;
  else
  {
    i = 0;
    found = false;
    while (i < MAX_TOUCH && !found)
    {
      if (touch[i].active == false)
      {
        touch[i].touchId = -1;
        found = true;
        break;
      }
      i++;
    }  
  }
  if (found)
    return i;
  return -1;
}

void alive(OSCMessage msg)
{
  int i=0;
  for (i = 0; i < MAX_TOUCH; i++)
  {
    touch[i].active = false;
  } 
  activeTouch = 0;
  int16_t scanTime = (int16_t) (micros() / 100);
  while (msg.isInt())
  {
      int s_id = msg.getInt();
      i = findTouchId(s_id);
      if (i >= 0 && touch[i].touchId == s_id)
      {
        touch[i].active = true;
        touch[i].ScanTime = scanTime;
        activeTouch++;
        //Serial.print("TUIO alive:");
        //Serial.print(s_id, DEC);
        //Serial.println(""); 
      }
    }
    //Serial.println("");
    //Serial.print("Active Touch ");
    //Serial.println(activeTouch, DEC);
    
    int j = 0;
    for (i = 0; i < MAX_TOUCH; i++)
    {
      if (touch[i].active)
      {
        TouchReport touchReport;
        touchReport.TipSwitch = 1;
        touchReport.x = touch[i].x;
        touchReport.y = touch[i].y;
        touchReport.ContactId = ((touch[i].touchId & 0xff00) >> 8) ^ (touch[i].touchId & 0xff);
        touchReport.ScanTime = touch[i].ScanTime;
        if (j == 0)
        {
          touchReport.ContactCount = activeTouch;
        }
        else
        {
          touchReport.ContactCount = 0;
        }
        j++;
        
        //Serial.print(" Simulated touchReport ");
        //Serial.print("TipSwitch ");
        //Serial.print(touchReport.TipSwitch, HEX);
        //Serial.print(", contactId ");
        //Serial.print(touchReport.ContactId, HEX);
        //Serial.print(" x ");
        //Serial.print(touchReport.x, DEC);
        //Serial.print(", y ");
        //Serial.print(touchReport.y, DEC);
        //Serial.print(", scan time ");
        //Serial.print(touchReport.ScanTime, HEX);
        //Serial.print(", contacts ");
        //Serial.print(touchReport.ContactCount, DEC);
        //Serial.println("");
            
        Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
        Serial.flush();
      }
    }
}

void set(OSCMessage msg)
{
    //Serial.print("TUIO set: ");
    int s_id = msg.getInt();
    int i = findTouchId(s_id);
    if (i >= 0)
    {
      float x = msg.getFloat(), y = msg.getFloat();
      float X = msg.getFloat(), Y = msg.getFloat();
      float m = msg.getFloat();
      touch[i].active = true;
      touch[i].x = x * MAX_X;
      touch[i].y = y * MAX_Y;
      touch[i].touchId = s_id;
      
      //Serial.print("s_id ");
      //Serial.print(s_id, DEC);
      //Serial.print(" x ");
      //Serial.print(x, DEC);
      //Serial.print(", y ");
      //Serial.print(y, DEC);
      // //Serial.print(" X ");
      // //Serial.print(X, DEC);
      // //Serial.print(", Y ");
      // //Serial.print(Y, DEC);
      // //Serial.print(" m ");
      // //Serial.print(m, DEC);
      //Serial.println("");
    }
}

void fseq(OSCMessage msg)
{
  //Serial.print("TUIO fsqe: ");
  int f_id = msg.getInt();
     
    // //Serial.print("f_id ");
    // //Serial.print(f_id, DEC);

    // //Serial.println(""); 
}

void tuioPacket(OSCMessage msg, int addrOffset )
{
   
  //Serial.print("Got msg size ");
  //Serial.print(msg.size(), DEC);
  //Serial.print(" bytes ");
  //Serial.println(msg.bytes(), DEC);  
  
  
  if (msg.isString())
  {
    char str[1024];
    msg.getString(str);
    
    if (strcmp(str, "alive") == 0)
    {
      alive(msg);
    }
    else if (strcmp(str, "set") == 0)
    {
      set(msg);
    }
    else if (strcmp(str, "fseq") == 0)
    {
      fseq(msg);
    }
  }
}
  
//reads and routes the incoming messages
void bundleReceive()
{ 
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    /*
    // //Serial.print("Received packet of size ");
    // //Serial.println(packetSize);
    // //Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      // //Serial.print(remote[i], DEC);
      if (i < 3)
      {
        // //Serial.print(".");
      }
    }
    // //Serial.print(", port ");
    // //Serial.println(Udp.remotePort());
    */
    if (bundleIN.receive()>0)
    {
/*      
       // //Serial.println("Got Bundle");

      OSCMessage msg = bundleIN.getMessage(0);
      if (msg.isString())
      {
        char str[1024];
        msg.getString(str);
        // //Serial.print(str);
        // //Serial.println("");
        msg.reset();
      }
*/  
      bundleIN.route("/tuio/2Dcur", tuioPacket);
    }
  }
}


 



