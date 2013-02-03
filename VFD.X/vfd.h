/* 
 * File:   vfd.h
 * Author: Bananas
 *
 * Created on February 2, 2013, 4:46 PM
 */

#ifndef VFD_H
#define	VFD_H

#define PORT_OUTPUT 0x00
#define OUTPUT 0
#define PORT_INPUT 0xFF
#define INPUT 1

#define DATA_TRIS TRISB
#define DATA LATB

#define WRITE_TRIS TRISDbits.TRISD7
#define WRITE LATDbits.LATD7

#define DATA_COMMAND_TRIS TRISDbits.TRISD6
#define DATA_COMMAND LATDbits.LATD6

#define READ_TRIS TRISDbits.TRISD5
#define READ LATDbits.LATD5

#define CHIP_SELECT_TRIS TRISDbits.TRISD4
#define CHIP_SELECT LATDbits.LATD4

#define BUSY_TRIS TRISDbits.TRISD3
#define BUSY LATDbits.LATD3


#define WRITE_DATA 0
#define WRITE_COMMAND 1
#define ENABLE_DISPLAY (CHIP_SELECT = 0)
#define DISABLE_DISPLAY (CHIP_SELECT = 1)
#define START_WRITE (WRITE = 0)
#define STOP_WRITE (WRITE = 1)

#define BACKSPACE 0x08
#define ADVANCE_CURSOR 0x09
#define LINE_FEED 0x0A
#define START_BLINK 0x0B
#define STOP_BLINK 0x0C
#define CARRIAGE_RETURN 0x0D
#define NORMAL 0x11
#define OVERWRITE 0x12
#define ENABLE_HORIZONTAL_SCROLL 0x13
#define MOVE_CURSOR 0x1B
#define RESET 0x40


void configurePICforVFD(void);
void writeCommand(auto unsigned char command);
void writeDataCommand(auto char data);
void writeCharacter(auto char character);
void writeCharacterAtPosition(auto char character, unsigned char position);
void writeString(auto char* string);
void writeRomString(const rom char* string);
void writeStringStartingAtPosition(auto char* string, unsigned char startPosition);
void writeRomStringStartingAtPosition(const rom char* string, unsigned char startPosition);
    
void clearDisplay(void);

#endif	/* VFD_H */

