#include "pic24_all.h"
#include "pic24_ports.h"
#include "vdip.h"
//#include <stdio.h>



/***********************************************************
 * Common Characters
 **********************************************************/

#define DIR_SPIWRITE 0
#define DIR_SPIREAD  1


//CS Pin configuration for VDIP1_A
#define VDIP1_A_ENABLE() _LATF0 = 1  //high true assertion
#define VDIP1_A_DISABLE() _LATF0 = 0

//CS Pin configuration for VDIP1_B
#define VDIP1_B_ENABLE() _LATB9 = 1  //high true assertion
#define VDIP1_B_DISABLE() _LATB9 = 0

//**********************************************************
/**
 * @brief Transfer data to/from the VDIP
 * @param[in] int The direction of the transfer
 * @param[out] uint8* The data to send or a buffer to fill
 */
//**********************************************************

/***********************************************************
*
*	John Rose's SPI_Xfer using Standard SPI - see above
*		
***********************************************************/

int SPI_Xfer(int spiDirection, uint8 *pSpiData)
{
	
	uint8 retData1 = 0;			
	uint8 retData2 = 0;	
	uint8 retData = 0;
	uint8 bitData_A =0;			//STATUS BIT_A
	uint8 bitData_B =0;			//STATUS BIT_B
	uint8 u8_spi = 0;			//Yeah, set to zero then assign; EE trick...
	u8_spi = *pSpiData;			//Data Passed to WRITE
	uint16 commandWord = 0;
  	_SPI2IF = 0;				//Clear SPI2 Flag; Redundant; Cleared in ioMasterSPI2()								
	VDIP1_A_ENABLE();			////VDIP1_A CS on
	
	switch(spiDirection)
	{
		//read operation from VDIP1_A
		case DIR_SPIREAD:
		retData1 = ioMasterSPI2(0xD0);  		//0b1100 0000    READ command
		retData2 = ioMasterSPI2(0x0);  			//0b0000 0000   Finish READ
		retData1 = (retData1 << 3);				//MS 5-bits
		bitData_A = (retData2 & 0x01);			//Status Bit
		retData2 = (retData2 >> 5);				//LS 3-bits
		VDIP1_A_DISABLE();						//VDIP1_A CS OFF
		ioMasterSPI2(0x00);						//Empty Clock
		retData = (retData1 | retData2);		//Merging
		
		DELAY_MS(10);

		//Must do a empty read on startup
		VDIP1_B_ENABLE();
		ioMasterSPI2(0xD0);  					//0b1100 0000    READ command
		ioMasterSPI2(0x0);  					//0b0000 0000   Finish READ
		VDIP1_B_DISABLE();						//VDIP1_B CS OFF
		ioMasterSPI2(0x00);						//Empty Clock

		//printf("%c", (uint8) retData);			//Need for Debugging UART For testing purposes
		*pSpiData = retData;
		break;

		// write operation
		case DIR_SPIWRITE:

		/***************************************************
		*
		*	d for Data Bit; x for don't care
		*	WRITE is two byte operation 
		*	followed by a empty clock byte
		*
		****************************************************/

		commandWord = (0x0400 | u8_spi);		//0b0000 0100 dddd dddd ;Merge WRITE command with Data Byte
		commandWord = (commandWord << 5);		//Shift to 0b100d dddd dddx xxxx 
		
		//VDIP1_A WRITE									
		u8_spi = (commandWord >> 8);			//MSB = 0b100d ddd
		ioMasterSPI2(u8_spi);					//Send MSB
		u8_spi = (commandWord & 0x00FF);		//LSB =0bdddd xxxx
		bitData_A = ioMasterSPI2(u8_spi);		//Send LSB and return Status bit
		VDIP1_A_DISABLE();						//VDIP1_A CS off
		u8_spi = ioMasterSPI2(0x00);			//Empty Clock	
		
		DELAY_MS(10);

		//VDIP1_B WRITE
		
		VDIP1_B_ENABLE();
		u8_spi = (commandWord >> 8);			//MSB = 0b100d ddd
		ioMasterSPI2(u8_spi);					//Send MSB
		u8_spi = (commandWord & 0x00FF);		//LSB =0bdddd xxxx
		bitData_B = ioMasterSPI2(u8_spi);		//Send LSB and return Status bit
		VDIP1_B_DISABLE();						//VDIP1_A CS off
		u8_spi = ioMasterSPI2(0x00);			//Empty Clock	
		*pSpiData = retData;
		break;
	


	}

	VDIP1_A_DISABLE();							//VDIP1_A CS off; redundant
	VDIP1_B_DISABLE();							//VDIP1_B CS off; redundant
	
	/*******************************************************
	*														
	*	STATUS BIT = VDIP1 Feedback from request
	*	A 1 is BAD!
	*		-Transmit Buffer Empty on READ request
	*		-Receive Buffer Full on WRITE request
	*	A 0 is GOOD!			
	*		-Transmition took place and everything is peachy...	
	*
	*	Need to add some better depth to IF STATEMENT BELOW
	*
	********************************************************/
	if(bitData_A){								//If 1...						
		DELAY_MS(10);							//Wait...
		bitData_A =0;								//And set to zero... It works so far	
	}
	if(bitData_B){								//If 1...						
		DELAY_MS(10);							//Wait...
		bitData_B =0;								//And set to zero... It works so far
		bitData_A = (bitData_A | bitData_B);	//Assign bitData_B to bitData_A
	}

	return bitData_A;							//Return Status bit
}

/***********************************************************
*
*	John Rose's SPI_Init using Standard SPI 
*
*	SPI2CON1 is a special registar that configures the SPI2 port.
*	SPI2STAT is a special registar that holds the Status of SPI2.
*
*	Before SPI2 is enable, all pins used must be configured as 
*	digital outputs.
*
*	Too enable the SPI2 port pins, SPIEN bit in the SPI2STAT registar
*	must be set.
*
*	SEE DATASHEET FOR DETAILS
*
***********************************************************/
void SPI_Init(void)
{
  //spi clock = 6MHz/1*1 = 6MHz/1 = 6MHz using our 12MHz crystal
 SPI2CON1 =  SEC_PRESCAL_1_1 |      //1:1 secondary prescale_M.N. //2:1 secondary prescale
             PRI_PRESCAL_1_1 |     //1:1 primary prescale
			 SPI_SMP_OFF  |		   //SMP = 1 Sample END clock
             CLK_POL_ACTIVE_HIGH | //clock active high (CKP = 0)
             SPI_CKE_ON          | //out changes active to inactive (CKE=1)
             SPI_MODE8_ON        | //8-bit mode
             MASTER_ENABLE_ON;     //master mode

 SPI2STATbits.SPIEN = 1;  			//enable SPI mode
 VDIP1_A_DISABLE();      			//disable the VDIP1_A
 VDIP1_B_DISABLE();					//M.N.
}

//**********************************************************
/**
 * @brief Wait till one character is read and then return it
 * @return uint8 The received character
 */
//**********************************************************
uint8 SPI_ReadWait(void)
{
	
	uint8 spiData = 0;

	while (SPI_Xfer(DIR_SPIREAD, &spiData))
    {
    	//outChar(spiData);
    }

    // If the new line isn't added, then the
    // uint8acters just overwrite each other, and
    // since a space is the last uint8acter before
    // the EOS, none of the output shows up.
    /*if(spiData == 0x0d)
    {
        spiData = '\n';
    } TED == IDIOT
	*/

    // printf("`%c`:`%x`\n", spiData, spiData);
    return spiData;
}

//**********************************************************
/**
 * @brief Non-blocking read of one uint8acter from SPI bus
 * @return uint8 The received uint8acter
 */
//**********************************************************
uint8 SPI_Read(uint8 *pSpiData)
{
	return SPI_Xfer(DIR_SPIREAD, pSpiData);
}

//**********************************************************
/**
 * @brief Blocking write of uint8acter to SPI bus
 * @param[in] uint8 The byte to be transmitted
 */
//**********************************************************
void SPI_Write(uint8 spiData)
{
	while(SPI_Xfer(DIR_SPIWRITE, &spiData));
}


//**********************************************************
/**
 * @brief Send a string of uint8acters to the SPI bus
 * @param[in] const uint8* The string to send
 */
//**********************************************************
void SPI_WriteStr(const uint8 *spiData)
{
    while(*spiData)
    {
        SPI_Write(*(spiData++));
    }

	// Carriage Return - every command needs one.
	SPI_Write(0x0d);
}


//**********************************************************
/**
 * @brief Send a string of uint8acters to the SPI bus
 * @param[in] const uint8* The string to send
 */
//**********************************************************
void SPI_WriteStrN(const uint8 *spiData, uint32 u32_size)
{
    uint32 u32_i;
    for(u32_i = 0; u32_i < u32_size; ++u32_i)
    {
        SPI_Write(spiData[u32_i]);
    }

	// Carriage Return - every command needs one.
	SPI_Write(0x0d);
}
