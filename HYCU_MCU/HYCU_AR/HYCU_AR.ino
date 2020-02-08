/*
HYCU - HYperscan Code Uploader by: ppcasm (ppcasm@gmail.com) (Arduino side)

Wiring Diagram:

Arduino - HyperScan Controller Port
pin 37 - RESET (Blue) //This is actually tied into SW2 Switch on Launchpad
pin 36 - ENABLE (Green)
pin 21 - CLK (Grey) 
pin 20 - DATA (Yellow)
GND - GND (Brown)

*/


void reset_hyperscan(void);
void send_byte(unsigned char bytez);

/*Arduino Mega
int led = 13; //Status
int clk = 37; //Clock
int data = 22; //Data
int reset = 22; //Reset
int enable = 30; //Enable
*/

//Arduino Uno
int led = 13; //Status
int clk = 19; //Clock
int data = 18; //Data
int reset = 2; //Reset
int enable = 3; //Enable

void setup() 
{                
  //pinMode(led, OUTPUT);   
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(reset, OUTPUT);
  //pinMode(enable, OUTPUT);
    
  //digitalWrite(led, LOW);
  digitalWrite(clk, LOW);
  digitalWrite(data, LOW);
  //digitalWrite(enable, LOW);
  //digitalWrite(reset, HIGH);

  //Bug in Arduino UNO forces max rate to 9600 baud
  //See: https://forum.arduino.cc/index.php?topic=512209.0
  Serial.begin(2400);
 
}

void loop()
{
  //reset_hyperscan();
  unsigned char testz = 0;
  for(;;)
  {
    if (Serial.available() > 0)
    {
      testz = Serial.read();
      noInterrupts();
      send_byte(testz);
      interrupts();
    }
  }

  return;
}

void reset_hyperscan()
{
  digitalWrite(reset, LOW);
  digitalWrite(led, LOW);
  
  delay(1000);
  
  digitalWrite(reset, HIGH);
  digitalWrite(led, HIGH);

  return;
}

//Send 8-bit value to HyperScan over raw wire
void send_byte(unsigned char bytez)
{
  /*
  Break down byte into wire HIGH/LOW. If the data bit is 0 then pull clock
  HIGH and pull data LOW. If the data bit is 1 then pull clock HIGH and data HIGH.
  */

  int x;
  int i = 0;
  for(x=0;x<8;x++)
  {

     
     if(bytez & (1<<x))
     {
    	digitalWrite(data, HIGH);
    	digitalWrite(clk, HIGH);
     }

    else
    {
    	digitalWrite(data, LOW);
    	digitalWrite(clk, HIGH);
    }
        digitalWrite(data, LOW);
        digitalWrite(clk, LOW);
    }
  
  return;
}
