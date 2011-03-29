#include "pic24_all.h"
#define VDIP_DEBUG 1
#include "vdip.h"




int main(void)
{
 	 //configure pins. Only need SDO, SCLK since POT is output only
	CONFIG_RG8_AS_DIG_OUTPUT();   //use RF3 for SDO
	CONFIG_RG6_AS_DIG_OUTPUT();   //use RF6 for SCLK
 	CONFIG_RG7_AS_DIG_OUTPUT();   //use RF7 for SDI
	CONFIG_RF0_AS_DIG_OUTPUT();   //chip select for VDIP1_A
	CONFIG_RB9_AS_DIG_OUTPUT();   //chip select for VDIP1_B

    configBasic(HELLO_MSG);

	outString("Hello world \n");
	configHeartbeat();            //heartbeat LED



	//config SPI for VDIP1
	VDIP_Init();

	VDIP_WriteFile("BARBIE.TXT", "THREE IS THE MAGICAL NUMBER.  YOUR HUBBY LOVES YOU!");
	VDIP_WriteFile("ABCDEF1.TXT", "This is a test.");
	VDIP_WriteFile("ABCDEF2.TXT", "This is a test.");
	VDIP_WriteFile("ABCDEF3.TXT", "This is a test.");
	VDIP_WriteFile("ABCDEF4.TXT", "This is a test.");
	VDIP_WriteFile("ABCDEF5.TXT", "This is a test.");
	VDIP_WriteFile("ABCDEF.TXT", "This is a test-1.");
	VDIP_WriteFile("ABCDEF.TXT", "This is a test-2.");
	VDIP_WriteFile("ABCDEF.TXT", "This is a test-3.");	
	VDIP_WriteFile("ABCDEF.TXT", "This is a test-4.");





//	VDIP_ListDir();
	while(1){}
	return 0;
}
