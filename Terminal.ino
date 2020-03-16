
#include <Arduino.h>
#include <U8x8lib.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>

#endif

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);



// setup the terminal (U8X8LOG) and connect to u8g2 for automatic refresh of the display
// The size (width * height) depends on the display 

#define U8LOG_WIDTH 16
#define U8LOG_HEIGHT 8
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8X8LOG u8x8log;



//const byte numChars = 82;
//char receivedChars[numChars];
//boolean newData = false;



void setup(void)
{
  Serial.begin(115200);
  mySerial.begin(115200);
  Serial.print("AT");
  //mySerial.print("AT");
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8log.begin(u8x8, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8x8log.setRedrawMode(1);		// 0: Update screen with newline, 1: Update screen for every char  
  pinMode(13, OUTPUT);
}

char  c1,c2;

void loop(void) {
    
  if (mySerial.available()) 
    {
      c1 =  mySerial.read();
      Serial.print(c1);
      u8x8log.print(c1);
      if (c1 == 'O') digitalWrite(13,HIGH);
      if (c1 == 'F') digitalWrite(13,LOW);
    }
  if (Serial.available()) 
    {
      c2 =  Serial.read();
      mySerial.print(c2);
      u8x8log.print(c2);
    }
  
  //else u8x8log.print("\n");
  
  
}


/*
void loop() {
    recvWithEndMarker();
    showNewData();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
   
    while (mySerial.available()  && newData == false) {
        rc = mySerial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        //Serial.print("This just in ... ");
        Serial.println(receivedChars);
        u8x8log.print(receivedChars);
        newData = false;
    }
}
*/
