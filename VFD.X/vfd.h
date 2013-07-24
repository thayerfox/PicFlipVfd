#ifndef VFD_H
#define	VFD_H

#include <p24Fxxxx.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define PORT_OUTPUT 0x00
#define OUTPUT 0
#define PORT_INPUT 0xFF
#define INPUT 1

#define DATA_TRIS
#define DATA

#define D0_TRIS TRISBbits.TRISB9
#define D0 LATBbits.LATB9
#define D1_TRIS TRISCbits.TRISC6
#define D1 LATCbits.LATC6
#define D2_TRIS TRISCbits.TRISC7
#define D2 LATCbits.LATC7
#define D3_TRIS TRISCbits.TRISC8
#define D3 LATCbits.LATC8
#define D4_TRIS TRISCbits.TRISC9
#define D4 LATCbits.LATC9
#define D5_TRIS TRISBbits.TRISB10
#define D5 LATBbits.LATB10
#define D6_TRIS TRISBbits.TRISB11
#define D6 LATBbits.LATB11
#define D7_TRIS TRISAbits.TRISA10
#define D7 LATAbits.LATA10

#define WRITE_TRIS TRISAbits.TRISA9
#define WRITE LATAbits.LATA9

#define DATA_COMMAND_TRIS TRISAbits.TRISA8
#define DATA_COMMAND LATAbits.LATA8

#define CHIP_SELECT_TRIS TRISAbits.TRISA7
#define CHIP_SELECT LATAbits.LATA7

#define READ_TRIS
#define READ

#define BUSY_TRIS
#define BUSY


#define WRITE_DATA 0
#define WRITE_COMMAND 1
//#define ENABLE_DISPLAY (CHIP_SELECT = 0)
//#define DISABLE_DISPLAY (CHIP_SELECT = 1)
//#define DO_WRITE_DATA do{WRITE = 0; Nop(); __delay_ms(1); WRITE = 1;} while(0)

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
#define VFD_RESET 0x40

typedef union _vfdData {
    struct {
        unsigned bit0:1;
        unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;
    } bits;
    char data;
} vfdData;

void configurePICforVFD(void);
void writeCommand(const vfdData *command);
void writeDataCommand(const vfdData *data);
void writeCharacter(const vfdData *character);
void writeCharacterAtPosition(const vfdData *character, vfdData *position);
void writeString(const vfdData **string);
void writeStringStartingAtPosition(const vfdData **string, vfdData *startPosition);
    
void clearDisplay(void);

#ifdef	__cplusplus
}
#endif


#endif	/* VFD_H */

