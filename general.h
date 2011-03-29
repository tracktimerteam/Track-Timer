// Chad's Header File to include basic functions
//
// This file is written as follows:
// (1) Pin Configurations - includes all functions and defines for needed I/O
//     (a) lane switches
//     (b) keypad
//     (c) lcd display
// (2) Keypad Functions - functions needed for keypad interface
// (3) LCD Functions - includes functions for communicating to LCD
// (4) General Functions - includes var defines, prints, structs and TIMER



/************************************PIN CONFIGURATIONS************************************/
/// Start/Stop configuration
inline void CONFIG_STARTSTOP()  
{
  CONFIG_RB1_AS_DIG_INPUT();     //use RB5 for switch input
  ENABLE_RB1_PULLUP();           //enable the pullup
  ENABLE_RB1_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SWSS         _RB1             //raw switch value
#define SWSS_PRESSED()   SWSS==0            //switch test
#define SWSS_RELEASED()  SWSS==1            //switch test

//1-8 lane switches
///////////////////////////////////////////////////////////
inline void CONFIG_SW1()  
{
  CONFIG_RB2_AS_DIG_INPUT();     //use RB6 for switch input
  ENABLE_RB2_PULLUP();           //enable the pullup
  ENABLE_RB2_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW1         _RB2             //raw switch value
#define SW1_PRESSED()   SW1==0            //switch test
#define SW1_RELEASED()  SW1==1            //switch test

inline void CONFIG_SW2()  
{
  CONFIG_RB3_AS_DIG_INPUT();     //use RB7 for switch input
  ENABLE_RB3_PULLUP();           //enable the pullup
  ENABLE_RB3_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW2         _RB3             //raw switch value
#define SW2_PRESSED()   SW2==0            //switch test
#define SW2_RELEASED()  SW2==1            //switch test

inline void CONFIG_SW3()  
{
  CONFIG_RB4_AS_DIG_INPUT();     //use RB8 for switch input
  ENABLE_RB4_PULLUP();           //enable the pullup
  ENABLE_RB4_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW3         _RB5             //raw switch value
#define SW3_PRESSED()   SW3==0            //switch test
#define SW3_RELEASED()  SW3==1            //switch test

inline void CONFIG_SW4()  
{
  CONFIG_RB5_AS_DIG_INPUT();     //use RB9 for switch input
  ENABLE_RB5_PULLUP();           //enable the pullup
  ENABLE_RB5_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW4         _RB5             //raw switch value
#define SW4_PRESSED()   SW4==0            //switch test
#define SW4_RELEASED()  SW4==1            //switch test

inline void CONFIG_SW5()  
{
  CONFIG_RD4_AS_DIG_INPUT();     //use RB10 for switch input
  ENABLE_RD4_PULLUP();           //enable the pullup
  ENABLE_RD4_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW5         _RD4             //raw switch value
#define SW5_PRESSED()   SW5==0            //switch test
#define SW5_RELEASED()  SW5==1            //switch test

inline void CONFIG_SW6()  
{
  CONFIG_RD5_AS_DIG_INPUT();     //use RB12 for switch input
  ENABLE_RD5_PULLUP();           //enable the pullup
  ENABLE_RD5_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW6         _RD5             //raw switch value
#define SW6_PRESSED()   SW6==0            //switch test
#define SW6_RELEASED()  SW6==1            //switch test

inline void CONFIG_SW7()  
{
  CONFIG_RD6_AS_DIG_INPUT();     //use RB13 for switch input
  ENABLE_RD6_PULLUP();           //enable the pullup
  ENABLE_RD6_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW7         _RD6             //raw switch value
#define SW7_PRESSED()   SW7==0            //switch test
#define SW7_RELEASED()  SW7==1            //switch test

inline void CONFIG_SW8()  
{
  CONFIG_RD7_AS_DIG_INPUT();     //use RB13 for switch input
  ENABLE_RD7_PULLUP();           //enable the pullup
  ENABLE_RD7_CN_INTERRUPT();     //CN5IE = 1
  DELAY_US(1);                    // Wait for pullup
}
#define SW8         _RD7             //raw switch value
#define SW8_PRESSED()   SW8==0            //switch test
#define SW8_RELEASED()  SW8==1            //switch test
////////////////////////////////////////////////////////


//////KEYPAD///////
#define KP1 _RB15		//#define C0 _RB9
#define KP2 _RF4		//#define C1 _RB8
#define KP3 _RF5		//#define C2 _RB7
#define KP4 _RG9		//#define C3 _RB6

static inline void CONFIG_COLUMN() 
{
  CONFIG_RB15_AS_DIG_INPUT();  ENABLE_RB15_PULLUP();
  CONFIG_RF4_AS_DIG_INPUT();  ENABLE_RF4_PULLUP();
  CONFIG_RF5_AS_DIG_INPUT();  ENABLE_RF5_PULLUP();
  CONFIG_RG9_AS_DIG_INPUT();  ENABLE_RG9_PULLUP();	
}

#define KP5 _LATE0		//#define R0 _LATB5
#define KP6 _LATE1		//#define R1 _LATB4
#define KP7 _LATE2		//#define R2 _LATB3
#define KP8 _LATE3		//#define R2 _LATB3

#define CONFIG_KP5_DIG_OUTPUT() CONFIG_RE0_AS_DIG_OUTPUT()
#define CONFIG_KP6_DIG_OUTPUT() CONFIG_RE1_AS_DIG_OUTPUT()
#define CONFIG_KP7_DIG_OUTPUT() CONFIG_RE2_AS_DIG_OUTPUT()
#define CONFIG_KP8_DIG_OUTPUT() CONFIG_RE3_AS_DIG_OUTPUT()

void CONFIG_ROW() 
{
  CONFIG_KP5_DIG_OUTPUT();
  CONFIG_KP6_DIG_OUTPUT();
  CONFIG_KP7_DIG_OUTPUT();
  CONFIG_KP8_DIG_OUTPUT();
}
///////KEYPAD////////


/////////LCD/////////
#define RS_HIGH()        _LATD8= 1
#define RS_LOW()         _LATD8 = 0
#define CONFIG_RS()      CONFIG_RD8_AS_DIG_OUTPUT()

#define RW_HIGH()        _LATD9 = 1
#define RW_LOW()         _LATD9 = 0
#define CONFIG_RW()      CONFIG_RD9_AS_DIG_OUTPUT()

#define E_HIGH()         _LATD10 = 1
#define E_LOW()          _LATD10 = 0
#define CONFIG_E()       CONFIG_RD10_AS_DIG_OUTPUT()

#define LCD4O          _LATD11
#define LCD5O          _LATD0
#define LCD6O          _LATC13
#define LCD7O          _LATC14
#define LCD7I          _RC14

#define CONFIG_LCD4_AS_INPUT() CONFIG_RD11_AS_DIG_INPUT()
#define CONFIG_LCD5_AS_INPUT() CONFIG_RD0_AS_DIG_INPUT()
#define CONFIG_LCD6_AS_INPUT() CONFIG_RC13_AS_DIG_INPUT()
#define CONFIG_LCD7_AS_INPUT() CONFIG_RC14_AS_DIG_INPUT()

#define CONFIG_LCD4_AS_OUTPUT() CONFIG_RD11_AS_DIG_OUTPUT()
#define CONFIG_LCD5_AS_OUTPUT() CONFIG_RD0_AS_DIG_OUTPUT()
#define CONFIG_LCD6_AS_OUTPUT() CONFIG_RC13_AS_DIG_OUTPUT()
#define CONFIG_LCD7_AS_OUTPUT() CONFIG_RC14_AS_DIG_OUTPUT()

#define GET_BUSY_FLAG()  LCD7I

//Configure 4-bit data bus for output
void configBusAsOutLCD(void) {
  RW_LOW();                  //RW=0 to stop LCD from driving pins
  CONFIG_LCD4_AS_OUTPUT();   //D4
  CONFIG_LCD5_AS_OUTPUT();   //D5
  CONFIG_LCD6_AS_OUTPUT();   //D6
  CONFIG_LCD7_AS_OUTPUT();   //D7
}

//Configure 4-bit data bus for input
void configBusAsInLCD(void) {
  CONFIG_LCD4_AS_INPUT();   //D4
  CONFIG_LCD5_AS_INPUT();   //D5
  CONFIG_LCD6_AS_INPUT();   //D6
  CONFIG_LCD7_AS_INPUT();   //D7
  RW_HIGH();                   // R/W = 1, for read
}
/////////LCD/////////


/////////VDIP/////////
//configure pins. Only need SDO, SCLK since POT is output only
void configVDIP(void){
  CONFIG_RG8_AS_DIG_OUTPUT();   //use RF3 for SDO
  CONFIG_RG6_AS_DIG_OUTPUT();   //use RF6 for SCLK
  CONFIG_RG7_AS_DIG_OUTPUT();   //use RF7 for SDI
  CONFIG_RF0_AS_DIG_OUTPUT();   //chip select for VDIP1_A
  CONFIG_RB9_AS_DIG_OUTPUT();   //chip select for VDIP1_B
}
/////////VDIP/////////
/************************************PIN CONFIGURATIONS************************************/



/************************************KEYPAD FUNCTIONS*************************************/
static inline void DRIVE_ROW_LOW() 
{  KP5=0;  KP6=0;  KP7=0;  KP8=0;	}

static inline void DRIVE_ROW_HIGH() 
{  KP5=1;  KP6=1;  KP7=1;  KP8=1;	}

void configKeypad(void) {
  CONFIG_ROW();
  DRIVE_ROW_LOW();
  CONFIG_COLUMN();
  DELAY_US(1);     //wait for pullups to stabilize inputs
}

//drive one row low
void setOneRowLow(uint8 u8_x) {
  switch (u8_x) {
    case 0:
      KP5 = 0;
      KP6 = 1;
      KP7 = 1;
      KP8 = 1;
      break;
    case 1:
      KP5 = 1;
      KP6 = 0;
      KP7 = 1;
      KP8 = 1;
      break;
    case 2:
      KP5 = 1;
      KP6 = 1;
      KP7 = 0;
      KP8 = 1;
      break;
    default:
      KP5 = 1;
      KP6 = 1;
      KP7 = 1;
      KP8 = 0;
      break;
  }
}
#define NUM_ROWS 4
#define NUM_COLS 4
const uint16 au16_keyTable[NUM_ROWS][NUM_COLS] = 
{ {'1', '5', '9', 'D' },
  {'2', '6', 'A', 'E' },
  {'3', '7', 'B', 'F'},
  {'4', '8', 'C', 'G'} };

//#define KEY_PRESSED() (!KP1 || !KP2 || !KP3 || !KP4)   //any low
#define KEY_PRESSED() ( (KP1==0) || (KP2==0) || (KP3==0) || (KP4==0) )   //any low
#define KEY_RELEASED() (KP1 &&  KP2 &&  KP3 &&  KP4)  //all high

uint8 doKeyScan(void) 
{
  uint8 u8_row, u8_col;
  //determine column
  if (!KP1) u8_col = 0;
  else if (!KP2) u8_col = 1;
  else if (!KP3) u8_col = 2;
  else if (!KP4) u8_col = 3;
  else return('E'); //error
  //determine row
  for (u8_row = 0; u8_row < NUM_ROWS; u8_row++) {
    setOneRowLow(u8_row); //enable one row low
    if (KEY_PRESSED()) {
      DRIVE_ROW_LOW(); //return rows to driving low
      return(au16_keyTable[u8_row][u8_col]);
    }
  }
  DRIVE_ROW_LOW(); //return rows to driving low
  return('E'); //error
}


typedef enum  {
  STATE_WAIT_FOR_PRESS = 0,
  STATE_WAIT_FOR_PRESS2,
  STATE_WAIT_FOR_RELEASE,
} ISRSTATE;

ISRSTATE e_isrState = STATE_WAIT_FOR_PRESS;
volatile uint16 u16_newKey = 0;
/************************************KEYPAD FUNCTIONS*************************************/



/*************************************LCD FUNCTIONS***************************************/
//Output lower 4-bits of u8_c to LCD data lines
void outputToBusLCD(uint8 u8_c) {
  LCD4O = u8_c & 0x01;          //D4
  LCD5O = (u8_c >> 1)& 0x01;    //D5
  LCD6O = (u8_c >> 2)& 0x01;    //D6
  LCD7O = (u8_c >> 3)& 0x01;    //D7
}

//Configure the control lines for the LCD
void configControlLCD(void) {
  CONFIG_RS();     //RS
  CONFIG_RW();     //RW
  CONFIG_E();      //E
  RW_LOW();
  E_LOW();
  RS_LOW();
}

//Pulse the E clock, 1 us delay around edges for
//setup/hold times
void pulseE(void) {
  DELAY_US(1);
  E_HIGH();
  DELAY_US(1);
  E_LOW();
  DELAY_US(1);
}

/* Write a byte (u8_Cmd) to the LCD.
u8_DataFlag is '1' if data byte, '0' if command byte
u8_CheckBusy is '1' if must poll busy bit before write, else simply delay before write
u8_Send8Bits is '1' if must send all 8 bits, else send only upper 4-bits
*/
void writeLCD(uint8 u8_Cmd, uint8 u8_DataFlag,
              uint8 u8_CheckBusy, uint8 u8_Send8Bits) {

  uint8 u8_BusyFlag;
  uint8 u8_wdtState;
  if (u8_CheckBusy) {
    RS_LOW();            //RS = 0 to check busy
    // check busy
    configBusAsInLCD();  //set data pins all inputs
    u8_wdtState = _SWDTEN;  //save WDT enable state
    CLRWDT();  			   //clear the WDT timer
    _SWDTEN = 1;            //enable WDT to escape infinite wait
    do {
      E_HIGH();
      DELAY_US(1);  // read upper 4 bits
      u8_BusyFlag = GET_BUSY_FLAG();
      E_LOW();
      DELAY_US(1);
      pulseE();              //pulse again for lower 4-bits
    } while (u8_BusyFlag);
    _SWDTEN = u8_wdtState;   //restore WDT enable state
  } else {
    DELAY_MS(10); // don't use busy, just delay
  }
  configBusAsOutLCD();
  if (u8_DataFlag) RS_HIGH();   // RS=1, data byte
  else    RS_LOW();             // RS=0, command byte
  outputToBusLCD(u8_Cmd >> 4);  // send upper 4 bits
  pulseE();
  if (u8_Send8Bits) {
    outputToBusLCD(u8_Cmd);     // send lower 4 bits
    pulseE();
  }
}

// Initialize the LCD, modify to suit your application and LCD
void initLCD() {
  DELAY_MS(50);          //wait for device to settle
  writeLCD(0x20,0,0,0); // 4 bit interface
  writeLCD(0x28,0,0,1); // 2 line display, 5x7 font
  writeLCD(0x28,0,0,1); // repeat
  writeLCD(0x06,0,0,1); // enable display
  writeLCD(0x0C,0,0,1); // turn display on; cursor, blink is off
  writeLCD(0x01,0,0,1); // clear display, move cursor to home
  DELAY_MS(3);
}

//Output a string to the LCD
void outStringLCD(char *psz_s) {
  while (*psz_s) {
    writeLCD(*psz_s, 1, 1,1);
    psz_s++;
  }
}
/*************************************LCD FUNCTIONS***************************************/



/************************************GENERAL FUNCTIONS************************************/
//volatile uint8 u8_valueSW1  = 1;    //initially high
uint16 minutes = 0;
uint16 seconds = 0;
uint16 millisecs = 0;

typedef struct  
{
  uint16 bib;
  uint16 mins;
  uint16 secs;
  uint16 msecs;
  uint8 active;
} recordedTime;

recordedTime times[80]; //603 yields 97% memory used... M.N.

typedef enum  
{
  STATE_RESET = 0,
  INIT_DEFAULT_CC,
  INIT_TRACK,
  LANE,
  NOLANE,
  START_OPTION_MENUOPTION,
  AUTO_DIM_MENUOPTION,
  ENTER_START_MENUOPTION,
  READY_MENUOPTION,
  START_OPTION_SINGLE,
  START_OPTION_MULTI,
  AUTO_DIM_ENABLE,
  AUTO_DIM_DISABLE,
  ENTER_START_ENABLE,
  ENTER_START_DISABLE,
  READY,
  READY_REL,
  READY_BEGIN,
  CC,
  CC_REL,
  TRACK,
  TRACK_REL,
  FINISH,
  FINISH_REC,
  FINISH_REL
} STATE;
STATE e_mystate;

#define ISR_PERIOD3     5                // in ms (for timing)
void  configTimer3(void) 
{
  //ensure that Timer2,3 configured as separate timers.
  T2CONbits.T32 = 0;     // 32-bit mode off
  //T3CON set like this for documentation purposes.
  //could be replaced by T3CON = 0x0020
  T3CON = T3_OFF |T3_IDLE_CON | T3_GATE_OFF
          | T3_SOURCE_INT
          | T3_PS_1_64 ;  //results in T3CON= 0x0020
  PR3 = msToU16Ticks (ISR_PERIOD3, getTimerPrescale(T3CONbits)) - 1;
  TMR3  = 0;                       //clear timer3 value
  _T3IF = 0;                       //clear interrupt flag
  _T3IP = 6;                       //choose a priority
  _T3IE = 1;                       //enable the interrupt
//  T3CONbits.TON = 1;               //turn on the timer
}

#define ISR_PERIOD4     50                // in ms (for keypad)
void  configTimer4(void) 
{
  //ensure that Timer2,3 configured as separate timers.
  T2CONbits.T32 = 0;     // 32-bit mode off
  //T3CON set like this for documentation purposes.
  //could be replaced by T3CON = 0x0020
  T4CON = T4_OFF |T4_IDLE_CON | T4_GATE_OFF
          | T4_SOURCE_INT
          | T4_PS_1_64 ;  //results in T3CON= 0x0020
  PR4 = msToU16Ticks (ISR_PERIOD4, getTimerPrescale(T4CONbits)) - 1;
  TMR4  = 0;                       //clear timer3 value
  _T4IF = 0;                       //clear interrupt flag
  _T4IP = 3;                       //choose a priority
  _T4IE = 1;                       //enable the interrupt
  T4CONbits.TON = 1;               //turn on the timer
}

//// timer5 used to update VDIP
#define ISR_PERIOD5     500              // in ms (VDIP_BUFFER)
void  configTimer5(void) 
{
  //ensure that Timer2,3 configured as separate timers.
  T2CONbits.T32 = 0;     // 32-bit mode off
  //T3CON set like this for documentation purposes.
  //could be replaced by T3CON = 0x0020
  T5CON = T5_OFF |T5_IDLE_CON | T5_GATE_OFF
          | T5_SOURCE_INT
          | T5_PS_1_64 ;  //results in T5CON= 0x0020
  PR5 = msToU16Ticks (ISR_PERIOD5, getTimerPrescale(T5CONbits)) - 1;
  TMR5  = 0;                       //clear timer3 value
  _T5IF = 0;                       //clear interrupt flag
  _T5IP = 1;                       //choose a priority
  _T5IE = 1;                       //enable the interrupt
//  T5CONbits.TON = 1;             //turn on the timer
}

//print debug message for state when it changes
void printNewState (STATE e_currentState) 
{
  static STATE e_LastState = STATE_RESET;
  if (e_LastState != e_currentState) 
  {
    switch (e_currentState) 
    {
      case INIT_DEFAULT_CC:
        outString("INIT_DEFAULT_CC\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Choose Mode");
        writeLCD(0xC0,0,1,1);
		outStringLCD("X-Country");
        break;
	  case INIT_TRACK:
		outString("INIT_TRACK\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Choose Mode");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Track");
		break;
      case LANE:
        outString("LANE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Lane Option");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Lane");
        break;
      case NOLANE:
        outString("NOLANE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Lane Option");
        writeLCD(0xC0,0,1,1);
		outStringLCD("No Lane");
        break;
//      case BIB_ENTRY1:
//        outString("NOLANE\n");
//		writeLCD(0x01,0,0,1);
//		outStringLCD("Lane Option");
//        writeLCD(0xC0,0,1,1);
//		outStringLCD("No Lane");
//        break;
	  case START_OPTION_MENUOPTION:
        outString("START_OPTION_MENUOPTION\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Main Menu");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Start Option");
        break;
	  case AUTO_DIM_MENUOPTION:
        outString("AUTO_DIM_MENUOPTION\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Main Menu");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Auto Dim");
        break;
	  case ENTER_START_MENUOPTION:
        outString("ENTER_START_MENUOPTION\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Main Menu");
        writeLCD(0xC0,0,1,1);
		outStringLCD("EnterAsStart");
        break;
	  case READY_MENUOPTION:
        outString("READY_MENUOPTION\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Main Menu");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Ready?");
        break;
	  case START_OPTION_SINGLE:
        outString("START_OPTION_SINGLE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Start Option");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Single");
        break;
	  case START_OPTION_MULTI:
        outString("START_OPTION_MULTI\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Start Option");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Multi");
        break;
	  case AUTO_DIM_ENABLE:
        outString("AUTO_DIM_ENABLE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Auto Dim");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Enable");
        break;
	  case AUTO_DIM_DISABLE:
        outString("AUTO_DIM_DISABLE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Auto Dim");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Disable");
        break;
	  case ENTER_START_ENABLE:
        outString("ENTER_START_ENABLE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("EnterAsStart");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Enable");
        break;
	  case ENTER_START_DISABLE:
        outString("ENTER_START_DISABLE\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("EnterAsStart");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Disable");
        break;
	  case READY:
        outString("READY\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Current Time");
        writeLCD(0xC0,0,1,1);
		outStringLCD("0:00:000");
        break;
	  case READY_REL:
        outString("READY_REL\n");
        break;
	  case READY_BEGIN:
        outString("READY_BEGIN\n");
        break;

	  // Cross Country Mode
      case CC:
        outString("CC - Timer Running\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("X-Country");
        break;
      case CC_REL:
        outString("CC_REL - Timer Ending\n");
        break;

	  // Track Mode
	  case TRACK:
		outString("TRACK - Timer Running\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Track Mode");
	 	break;
	  case TRACK_REL:
		outString("TRACK_REL - Timer Ending\n");
	 	break;

      case FINISH:
        outString("FINISH\n");
		writeLCD(0x01,0,0,1);
		outStringLCD("Finished...");
        writeLCD(0xC0,0,1,1);
		outStringLCD("Press Enter");
        break;
      case FINISH_REC:
        outString("FINISH_REC - Reporting Times\n");
        break;
      case FINISH_REL:
        outString("FINISH_REL - Going to INIT_DEFAULT_CC\n");
        break;
      case STATE_RESET:
        outString("STATE_RESET\n");
        break;
      default:
        break;
    }
  }
  e_LastState = e_currentState;  //remember last state
}

void config_pushbuttons(void) {
  CONFIG_STARTSTOP();
  CONFIG_SW1();        
  CONFIG_SW2();
  CONFIG_SW3();
  CONFIG_SW4();
  CONFIG_SW5();
  CONFIG_SW6();
  CONFIG_SW7();
  CONFIG_SW8();
}

/************************************GENERAL FUNCTIONS************************************/