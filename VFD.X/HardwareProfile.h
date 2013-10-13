#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

// Define your clock speed here

// Sample clock speed for PIC18

    #define GetSystemClock()        32000000
    #define GetPeripheralClock()    GetSystemClock()
    #define GetInstructionClock()   (GetSystemClock() / 2)

    // Clock values
    #define MILLISECONDS_PER_TICK       10                      // Definition for use with a tick timer
    #define TIMER_PRESCALER             TIMER_PRESCALER_8       // Definition for use with a tick timer
    #define TIMER_PERIOD                20000                   // Definition for use with a tick timer


// Description: Macro used to enable the SD-SPI physical layer (SD-SPI.c and .h)
#define USE_SD_INTERFACE_WITH_SPI

// Description: Macro used to enable the CF-PMP physical layer (CF-PMP.c and .h)
//#define USE_CF_INTERFACE_WITH_PMP

// Description: Macro used to enable the CF-Manual physical layer (CF-Bit transaction.c and .h)                                                                
//#define USE_MANUAL_CF_INTERFACE

// Description: Macro used to enable the USB Host physical layer (USB host MSD library)
//#define USE_USB_INTERFACE


/*********************************************************************/
/******************* Pin and Register Definitions ********************/
/*********************************************************************/

/* SD Card definitions: Change these to fit your application when using
   an SD-card-based physical layer                                   */



		
	        // Description: SD-SPI Chip Select Output bit
	        #define SD_CS	LATCbits.LATC0
	        // Description: SD-SPI Chip Select TRIS bit
	        #define SD_CS_TRIS  TRISCbits.TRISC0

	        // Description: SD-SPI Card Detect Input bit
	        #define SD_CD               0
	        // Description: SD-SPI Card Detect TRIS bit
	        #define SD_CD_TRIS          0
	        
	        // Description: SD-SPI Write Protect Check Input bit
	        #define SD_WE              0
	        // Description: SD-SPI Write Protect Check TRIS bit
	        #define SD_WE_TRIS          0
	        
	        // Registers for the SPI module you want to use

	        // Description: The main SPI control register
	        #define SPICON1             SPI1CON1
	        // Description: The SPI status register
	        #define SPISTAT             SPI1STAT
	        // Description: The SPI Buffer
	        #define SPIBUF              SPI1BUF
	        // Description: The receive buffer full bit in the SPI status register
	        #define SPISTAT_RBF         SPI1STATbits.SPIRBF
	        // Description: The bitwise define for the SPI control register (i.e. _____bits)
	        #define SPICON1bits         SPI1CON1bits
	        // Description: The bitwise define for the SPI status register (i.e. _____bits)
	        #define SPISTATbits         SPI1STATbits
	        // Description: The enable bit for the SPI module
	        #define SPIENABLE           SPI1STATbits.SPIEN

	        // Tris pins for SCK/SDI/SDO lines

	        // Description: The TRIS bit for the SCK pin
	        #define SPICLOCK            TRISCbits.TRISC4
	        // Description: The TRIS bit for the SDI pin
	        #define SPIIN               TRISCbits.TRISC2
	        // Description: The TRIS bit for the SDO pin
	        #define SPIOUT              TRISCbits.TRISC1

	

#endif
