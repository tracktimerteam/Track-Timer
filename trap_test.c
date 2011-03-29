/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */

#include "pic24_all.h"
#include "general.h"
#include "vdip.h"
#include <stdio.h>
#include <string.h> 


/***********************************************************
 * Macro Definitions
 **********************************************************/
#define MainDebug 1
// Is the main debug build?
#ifndef MainDebug
#define MainDebug 0
#endif // VDIP_DEBUG

// Print output if this is a VDIP_DEBUG build
#if MainDebug
#define MainDebug(msg) \
    (outString("~"msg" :)\n"))
#else
#define MainDebug(msg)
#endif

//Example: MainDebug("Buffer 5: 2.5332");



//Interrupt Service Routine for Timer3
void _ISRFAST _T3Interrupt (void) 
{
  /**********************timing**************************/
  millisecs = millisecs + ISR_PERIOD3;
  if ( millisecs >= 1000 )
  {
	seconds = seconds + 1;
    millisecs = 0;
  }
  if ( (millisecs % 100) == 0 )
  {
    updateLCD( seconds, millisecs );
  }
//  if ( seconds >= 60 )
//  {
//    minutes = minutes + 1;
//    seconds = 0;
//  }

//  writeLCD(0xC0,0,1,1);  // cursor to 2nd line and clears 2nd line
//
//  char sec[12];                char msec[12];                 char min[12];
//  sprintf(sec, "%u", seconds); sprintf(msec, "%u", millisecs); sprintf(min, "%u", minutes);
//
//  outStringLCD( min ); outStringLCD(":");
//  outStringLCD( sec ); outStringLCD(":");
//  outStringLCD( msec);
//  printf( "\n%u : %u : %u\n", minutes, seconds, millisecs );
  /**********************timing**************************/

  _T3IF = 0;                 //clear the timer interrupt bit
}
void updateLCD(uint16 seconds, uint16 millisecs)
{
  writeLCD(0xC0,0,1,1);  // cursor to 2nd line and clears 2nd line

  int minutes = seconds/60;
  seconds = seconds - (minutes*60);
  char sec[12];                char msec[12];                  char min[12];
  sprintf(sec, "%u", seconds); sprintf(msec, "%u", millisecs); sprintf(min, "%u", minutes);

  outStringLCD( min ); outStringLCD(":");
  outStringLCD( sec ); outStringLCD(":");
  outStringLCD( msec);
}

//Interrupt Service Routine for Timer4 (keypad)
void _ISRFAST _T4Interrupt (void) 
{
  /**********************keypad**************************/
    switch (e_isrState) {
    case STATE_WAIT_FOR_PRESS:
      if (KEY_PRESSED() && (u16_newKey == 0)) {
        //ensure that key is sampled low for two consecutive interrupt periods
        e_isrState = STATE_WAIT_FOR_PRESS2;
      }
      break;
    case STATE_WAIT_FOR_PRESS2:
      if (KEY_PRESSED()) {
        // a key is ready
        u16_newKey = doKeyScan();
        e_isrState = STATE_WAIT_FOR_RELEASE;
      } else e_isrState = STATE_WAIT_FOR_PRESS;
      break;

    case STATE_WAIT_FOR_RELEASE:
      //keypad released
      if (KEY_RELEASED()) {
        e_isrState = STATE_WAIT_FOR_PRESS;
      }
      break;
    default:
      e_isrState = STATE_WAIT_FOR_PRESS;
      break;
    }
  /**********************keypad**************************/

  _T4IF = 0;                 //clear the timer interrupt bit
}



uint16 x=0;

void _ISRFAST _CNInterrupt (void) 
{
	switch (e_mystate)
	{
		case CC:
			if (SW1_PRESSED())
			{
				x++;
					times[x].msecs = millisecs;
					times[x].secs = seconds;
			 		times[x].active = 1;
					char str_sec[12];
					sprintf(str_sec, "%u"".%u\n", times[x].secs,times[x].msecs);
					printf("time %u: %s",x,str_sec);
					
			T5CONbits.TON=1;
			}
           
			break;
		case TRACK:
			if ( SW1_PRESSED() && times[0].active == 0 )
			{
			    times[0].msecs = millisecs;				times[0].secs = seconds;				times[0].mins = minutes;				times[0].active = 1;
			}
			if ( SW2_PRESSED() && times[1].active == 0 )
			{
			    times[1].msecs = millisecs;				times[1].secs = seconds;				times[1].mins = minutes;				times[1].active = 1;
			}
			if ( SW3_PRESSED() && times[2].active == 0 )
			{
			    times[2].msecs = millisecs;				times[2].secs = seconds;				times[2].mins = minutes;				times[2].active = 1;
			}
			if ( SW4_PRESSED() && times[3].active == 0 )
			{
			    times[3].msecs = millisecs;				times[3].secs = seconds;				times[3].mins = minutes;				times[3].active = 1;
			}
			if ( SW5_PRESSED() && times[4].active == 0 )
			{
			    times[4].msecs = millisecs;				times[4].secs = seconds;				times[4].mins = minutes;				times[4].active = 1;
			}
			if ( SW6_PRESSED() && times[5].active == 0 )
			{
			    times[5].msecs = millisecs;				times[5].secs = seconds;				times[5].mins = minutes;				times[5].active = 1;
			}
			if ( SW7_PRESSED() && times[6].active == 0 )
			{
			    times[6].msecs = millisecs;				times[6].secs = seconds;				times[6].mins = minutes;				times[6].active = 1;
			}
			if ( SW8_PRESSED() && times[7].active == 0 )
			{
			    times[7].msecs = millisecs;				times[7].secs = seconds;				times[7].mins = minutes;				times[7].active = 1;
			}
			break;
	}
	DELAY_MS(100); // Debouncing delay
   _CNIF = 0;    //clear the change notification interrupt bit
}

//Interrupt Service Routine for Timer5 (UPDating VDIP1s)

uint16 buffer=1;
void _ISRFAST _T5Interrupt (void) 
{
  
//printf("\nx:%d""buffer:%d\n",x,buffer);

while(buffer<=x){

DELAY_MS(500);
	char str_secb[12];
	sprintf(str_secb, "%u"".%u\n", times[buffer].secs,times[buffer].msecs);
	printf("buffer %u: %s", buffer, str_secb);
	VDIP_WriteFile("ohyeah.txt", str_secb);
buffer++;
}
_T5IF = 0; 
printf("\nbuffer turned off\n");
T5CONbits.TON=0;}
                //clear the timer interrupt bit





int main (void) {

  configBasic(HELLO_MSG);      			// Set up heartbeat, UART, print hello message and diags
  configVDIP();			   
  VDIP_Init();
  configKeypad();
  configControlLCD();      //configure the LCD control lines
  initLCD();               //initialize the LCD
  config_pushbuttons();
 							 				
  MainDebug("MainDebug on");

//Placed here just to test the VDIPS // M.N.
//VDIP_WriteFile("Track.txt", "abc");		//Please make sure that the file name 	M.N. //plus file extension does not exceed 13 characters. M.N.
//VDIP_DiskExists();
//VDIP_PrintListDir();



   /** Configure Change Notification general interrupt  */
  _CNIF = 0;         //Clear the interrupt flag
  _CNIP = 3;         //Choose a priority
  _CNIE = 1;         //enable the Change Notification general interrupt
  /** Configure the Timer */
  configTimer3();
  configTimer4();
  configTimer5();	// M.N. VDIP BUFFER


    /*****Toggle LED each time switch is pressed and released ******************************/
  e_mystate = INIT_DEFAULT_CC;

  // track or cross country
  uint8 mode = 0;     // 0=cross country
				      // 1=track

  // allows feature use 3 or 1 plungers to start timer
  uint8 lane = 1;     // 0=no lane (applied to track only)
					  // 1=lane    (applied to track only)

  // will dim LCD backlight after 10 seconds
  uint8 autoDim = 1;  // 0=disabled
					  // 1=enabled

  // will allow to start timer by pressing "enter" on keypad
  uint8 entStart = 1; // 0=disabled
					  // 1=enabled

  // allows feature use 3 or 1 plungers to start timer
  uint8 startOpt = 0; // 0=single
					  // 1=multi

  uint16 y=0;

  writeLCD(0x01,0,0,1); // clear display, move cursor to home
  outStringLCD( "TrackTimer" );
  writeLCD(0xC0,0,1,1);  // cursor to 2nd line and clears 2nd line
  outStringLCD( "Welcome..." );

  DELAY_MS( 300 );

  while (1) 
  {
y=0;
    printNewState(e_mystate);  //debug message when state changes

    switch (e_mystate) 
    {
	  /***********************************************************
	  * Initial Selection - Choose between "Track" and "X-Country
	  **********************************************************/
      case INIT_DEFAULT_CC:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = INIT_TRACK;    
		  else if ( u16_newKey=='G' )
		  {
			mode = 0;
			e_mystate = START_OPTION_MENUOPTION;   
		  }
		  u16_newKey = 0;
		}
        break;
	  case INIT_TRACK:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = INIT_DEFAULT_CC;     
		  else if ( u16_newKey=='G' )
		  {
			mode = 1;
			e_mystate = LANE;
		  }
		  u16_newKey = 0;
		}
        break;

	  /***********************************************************
	  * If "Track" is selected, now choose "Lane" or "No Lane"
	  **********************************************************/
	  case LANE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = NOLANE;     
		  else if ( u16_newKey=='G' )
		  {
			lane = 1;
			e_mystate = START_OPTION_MENUOPTION;  
		  }
		  u16_newKey = 0;
		}
        break;
	  case NOLANE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = LANE;        
		  else if ( u16_newKey=='G' )
		  {
			lane = 0;
			e_mystate = START_OPTION_MENUOPTION;	
		  }
		  u16_newKey = 0;
		}
        break;

	  /***********************************************************
	  * BIB Number Entry
	  **********************************************************/
//	  case BIB_ENTRY1:
//		if ( u16_newKey )
//		{
//		  if ( u16_newKey=='4' || u16_newKey=='8' )
//			e_mystate = LANE;        
//		  else if ( u16_newKey=='G' )
//		  {
//			lane = 0;
//			e_mystate = START_OPTION_MENUOPTION;	
//		  }
//		  u16_newKey = 0;
//		}
//        break;
																						//INSERT BIB ENTRY PAGE
	  /***********************************************************
	  * Typical Device Settings - (scrollable)
	  **********************************************************/
	  case START_OPTION_MENUOPTION:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' )				//press UP
			e_mystate = READY_MENUOPTION;     
		  else if ( u16_newKey=='8' )			//press DOWN
			e_mystate = AUTO_DIM_MENUOPTION;     
		  else if ( u16_newKey=='G' )			//press ENTER
			e_mystate = START_OPTION_SINGLE;  

		  u16_newKey = 0;
		}
        break;
	  case AUTO_DIM_MENUOPTION:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' )				//press UP
			e_mystate = START_OPTION_MENUOPTION;     
		  else if ( u16_newKey=='8' )			//press DOWN
			e_mystate = ENTER_START_MENUOPTION;     
		  else if ( u16_newKey=='G' )			//press ENTER
			e_mystate = AUTO_DIM_ENABLE;  

		  u16_newKey = 0;
		}
        break;
	  case ENTER_START_MENUOPTION:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' )				//press UP
			e_mystate = AUTO_DIM_MENUOPTION;     
		  else if ( u16_newKey=='8' )			//press DOWN
			e_mystate = READY_MENUOPTION;     
		  else if ( u16_newKey=='G' )			//press ENTER
			e_mystate = ENTER_START_DISABLE;  

		  u16_newKey = 0;
		}
        break;
	  case READY_MENUOPTION:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' )				//press UP
			e_mystate = ENTER_START_MENUOPTION;     
		  else if ( u16_newKey=='8' )			//press DOWN
			e_mystate = START_OPTION_MENUOPTION;     
		  else if ( u16_newKey=='G' )			//press ENTER
			e_mystate = READY;  

		  u16_newKey = 0;
		}
        break;

	  /***********************************************************
	  * Individual Settings - screens to set/reset options
	  **********************************************************/
///////////////// Start Option /////////////////////////////
	  case START_OPTION_SINGLE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = START_OPTION_MULTI;        
		  else if ( u16_newKey=='G' )
		  {
			startOpt = 0;
			e_mystate = START_OPTION_MENUOPTION;								//input confirmation screen for 3 seconds (just a suggestion)	
		  }
		  u16_newKey = 0;
		}
        break;
	  case START_OPTION_MULTI:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = START_OPTION_SINGLE;        
		  else if ( u16_newKey=='G' )
		  {
			startOpt = 1;
			e_mystate = START_OPTION_MENUOPTION;	
		  }
		  u16_newKey = 0;
		}
        break;
/////////////// Auto Dim (feature) //////////////////////////
	  case AUTO_DIM_ENABLE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = AUTO_DIM_DISABLE;        
		  else if ( u16_newKey=='G' )
		  {
			autoDim = 1;
			e_mystate = AUTO_DIM_MENUOPTION;
		  }
		  u16_newKey = 0;
		}
        break;
	  case AUTO_DIM_DISABLE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = AUTO_DIM_ENABLE;        
		  else if ( u16_newKey=='G' )
		  {
			autoDim = 0;
			e_mystate = AUTO_DIM_MENUOPTION;	
		  }
		  u16_newKey = 0;
		}
        break;
/////////////// Enter as Start (feature) //////////////////////////
	  case ENTER_START_ENABLE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = ENTER_START_DISABLE;        
		  else if ( u16_newKey=='G' )
		  {
			entStart = 1;
			e_mystate = ENTER_START_MENUOPTION;	
		  }
		  u16_newKey = 0;
		}
        break;
	  case ENTER_START_DISABLE:
		if ( u16_newKey )
		{
		  if ( u16_newKey=='4' || u16_newKey=='8' )
			e_mystate = ENTER_START_ENABLE;        
		  else if ( u16_newKey=='G' )
		  {
			entStart = 0;
			e_mystate = ENTER_START_MENUOPTION;	
		  }
		  u16_newKey = 0;
		}
        break;




//check all flag bits and route accordingly
	  case READY:
		if ( SWSS_PRESSED() )
		  e_mystate = READY_REL;
		else if ( entStart == 1 )
		{
			if ( u16_newKey )
			{
			  if ( u16_newKey=='G' )		//press "Enter" to begin race
				e_mystate = READY_BEGIN;
			  u16_newKey = 0;
			}
		}
		break;
      case READY_REL:
        if ( SWSS_RELEASED() )
		  e_mystate = READY_BEGIN;
        break;
	  case READY_BEGIN:
		if ( mode == 1 )
		  e_mystate = TRACK;
		else
		  e_mystate = CC;
	    T3CONbits.TON = 1;               //turn on the timer
		break;

	  //Cross Country
      case CC:
		if ( SWSS_PRESSED() )
		{
			T3CONbits.TON = 0;               //turn off the timer
			e_mystate = CC_REL;
		}
		else if ( u16_newKey=='G' )
		{
		  T3CONbits.TON = 0;               //turn off the timer
		  u16_newKey = 0;
		  e_mystate = FINISH_REC;
		}
		else
			e_mystate = CC;
        break;
      case CC_REL:
        if ( SWSS_RELEASED() ) 
          e_mystate = FINISH_REC;
        break;
	  //Track
      case TRACK:	  
        if ( SWSS_PRESSED() ) 
        {
		  T3CONbits.TON = 0;               //turn off the timer
          e_mystate = TRACK_REL;
        }
        break;
      case TRACK_REL:
        if ( SWSS_RELEASED() ) 
          e_mystate = FINISH_REC;
        break;


      case FINISH_REC:
		// print to files?

//		while (times[y].active == 1)
//		{
//         printf( "Recorded Time #%1.0f:  %1.0f:%1.0f:%1.0f \n", 
//			         (double)y, (double)times[y].mins, (double)times[y].secs, (double)times[y].msecs );
//		  y = y+1;
//		}
        e_mystate = FINISH;
        break;
      case FINISH:
        if (SWSS_PRESSED())
        {
		  y=0;
          e_mystate = FINISH_REL;
        }
		else if ( u16_newKey )
		{
		  if (u16_newKey=='G')
		    e_mystate = INIT_DEFAULT_CC;
		  u16_newKey = 0;
		}
        break;
      case FINISH_REL:
        if ( SWSS_RELEASED() )
          e_mystate = INIT_DEFAULT_CC;
        break;
      default:
        e_mystate = INIT_DEFAULT_CC;
    }//end switch(e_mystate)
    //doHeartbeat();     //ensure that we are alive
  } // end while (1)

}

