/*
HYCU - HYperscan Code Uploader by: ppcasm (ppcasm@gmail.com) (MSP430/TI Launchpad side)

Wiring Diagram:

MSP430 - HyperScan Controller Port
P1.3 - RESET (Blue) //This is actually tied into SW2 Switch on Launchpad
P1.4 - ENABLE (Green)
P1.6 - CLK (Grey) //This is actually tied to LED2 on Launchpad
P1.7 - DATA (Yellow)
GND - GND (Brown)

*/

#include <msp430g2553.h>
#include <string.h>

//Baud Rate
#define BAUDZ 9600 //9600 Baud

//CPU Clock Speed
#define CLOCKZ 1000000 //1MHZ

//UART
#define UART_TXD 0x2
#define UART_RXD 0x4
#define UART_TBIT_DIV_2 (CLOCKZ / (BAUDZ * 2))
#define UART_TBIT (CLOCKZ / BAUDZ)
unsigned int txData; //UART internal variable for TX
unsigned char rxBuffer; //Received UART character

//I2C/Custom Serial
#define RESETZ 1<<3
#define ENABLEZ 1<<4
#define CLKZ 1<<6
#define DATAZ 1<<7

//Prototypes
void Reset_HyperScan(void);
void send_byte(unsigned char byte);
void UART_init(void);
void UART_tx(unsigned char byte);
void UART_print(char *string);

int main(void)
{
	  //Stop watchdog timer
	  WDTCTL = WDTPW + WDTHOLD;
	  if (CALBC1_1MHZ==0xFF) //If calibration value has been erased
	  {
	 	  while(1); //Lock up
	  }

	  //Configure Osc
	  DCOCTL = 0; //Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ; //Set DCOCLK to 1MHz
      DCOCTL = CALDCO_1MHZ;

      //Configure port settings
      P1OUT |= RESETZ; //Take HyperScan out of reset
      P1OUT &= ~(CLKZ); //CLK = LOW
      P1OUT &= ~(DATAZ); //DATA = LOW

      P1SEL = UART_TXD + UART_RXD; //Timer function for TXD/RXD pins

      P1DIR & ~UART_RXD; //Input
      P1DIR &= ~(ENABLEZ); // Input
      P1DIR |= RESETZ; // Output
      P1DIR |= CLKZ; // Output
      P1DIR |= DATAZ; // Output
      P1DIR |= UART_TXD; //Output

	  __enable_interrupt();

	  UART_init(); //Initialize UART

	  //Send "magic"
	  //UART_print("HYCU");

	  //UART_print("READY.\n");
      int i = 0;
	  for (;;)
	  {
		  //Wait for incoming character
	      __bis_SR_register(LPM0_bits);

	      //Handler stuffs
	      __disable_interrupt();
	      send_byte(rxBuffer); //rxBuffer);
	      __enable_interrupt();
	      //for(i=0;i<0xffff;i++){}

	      //Echo received character
	      //UART_tx(rxBuffer);
	  }

      return 0;
}

//Send reset pulse to HyperScan
void Reset_HyperScan()
{
	int i = 0;
	for(i=0;i<0xffff;i++) P1OUT &= ~(RESETZ); //Do reset
	P1OUT |= RESETZ; //Take out of reset

	return;
}

//Send 8-bit value to HyperScan over raw wire
void send_byte(unsigned char byte)
{
     /*
     Break down byte into wire HIGH/LOW. If the data bit is 0 then pull clock
     HIGH and pull data LOW. If the data bit is 1 then pull clock HIGH and data HIGH.
    */

    int x;
    int i = 0;
    for(x=0;x<8;x++)
    {

    	//1: CLK = HIGH - DATA = HIGH
    	if(byte & (1<<x))
    	{
    		P1OUT |= DATAZ;
    		//for(i=0;i<0xffff;i++){}
    		P1OUT |= CLKZ;
    		//for(i=0;i<0xffff;i++){}

       	}

    	//0: CLK = HIGH - DATA = LOW
    	else
    	{
    		P1OUT &= ~(DATAZ);
    		//for(i=0;i<0xffff;i++){}
    		P1OUT |= CLKZ;
    		//for(i=0;i<0xffff;i++){}

      	}


    	P1OUT &= ~(DATAZ); //Pull DATA LOW
    	P1OUT &= ~(CLKZ); //Pull CLK LOW
    	//for(i=0;i<0xffff;i++){}

    }





    return;
}

//Configure Timer_A for full-duplex UART operation
void UART_init(void)
{
    TACCTL0 = OUT; //Set TXD Idle as Mark = '1'
    TACCTL1 = SCS + CM1 + CAP + CCIE; //Sync, Neg Edge, Capture, Int
    TACTL = TASSEL_2 + MC_2; //SMCLK, start in continuous mode
}

//Output one byte using the Timer_A UART
void UART_tx(unsigned char byte)
{
    while (TACCTL0 & CCIE); //Ensure last char got TX'd
    TACCR0 = TAR; //Current state of TA counter
    TACCR0 += UART_TBIT; //One bit time till first bit
    TACCTL0 = OUTMOD0 + CCIE; //Set TXD on EQU0, Int
    txData = byte; //Load global variable
    txData |= 0x100; //Add mark stop bit to TXData
    txData <<= 1; //Add space start bit
}

//Print a string over using the Timer_A UART
void UART_print(char *string)
{
    while (*string)
    {
        UART_tx(*string++);
    }
}

//Interrupt Handlers

//Timer_A UART - Transmit Interrupt Handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    static unsigned char txBitCnt = 10;

    TACCR0 += UART_TBIT; //Add Offset to CCRx
    if (txBitCnt == 0) //All bits TXed?
    {
        TACCTL0 &= ~CCIE; //All bits TXed, disable interrupt
        txBitCnt = 10; // Re-load bit counter
    }

    else
    {
        if (txData & 0x01)
        {
          TACCTL0 &= ~OUTMOD2; // TX Mark '1'
        }

        else
        {
          TACCTL0 |= OUTMOD2; // TX Space '0'
        }
        txData >>= 1;
        txBitCnt--;
    }
}

//Timer_A UART Receive Interrupt Handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1_ISR(void)
{
    static unsigned char rxBitCnt = 8;
    static unsigned char rxData = 0;

    switch (__even_in_range(TA0IV, TA0IV_TAIFG)) //Use calculated branching
    {
        case TA0IV_TACCR1: //TACCR1 CCIFG - UART RX
            TACCR1 += UART_TBIT; //Add Offset to CCRx
            if (TACCTL1 & CAP) //Capture mode = start bit edge
            {
                TACCTL1 &= ~CAP; //Switch capture to compare mode
                TACCR1 += UART_TBIT_DIV_2; //Point CCRx to middle of D0
            }

            else
            {
                rxData >>= 1;
                if (TACCTL1 & SCCI) //Get bit waiting in receive latch
                {
                    rxData |= 0x80;
                }
                rxBitCnt--;

                if (rxBitCnt == 0) //All bits RXed?
                {
                    rxBuffer = rxData; //Store in global variable
                    rxBitCnt = 8; //Re-load bit counter
                    TACCTL1 |= CAP; //Switch compare to capture mode
                    __bic_SR_register_on_exit(LPM0_bits); //Clear LPM0 bits from 0(SR)
                }
            }
            break;
    }
}
