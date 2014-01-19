#ifndef VFD_H
#define	VFD_H

#include <xc.h>

#define PORT_OUTPUT 0x00
#define OUTPUT 0
#define PORT_INPUT 0xFF
#define INPUT 1

#define VFD_D0_TRIS TRISBbits.TRISB9
#define VFD_D0 LATBbits.LATB9
#define VFD_D1_TRIS TRISCbits.TRISC6
#define VFD_D1 LATCbits.LATC6
#define VFD_D2_TRIS TRISCbits.TRISC7
#define VFD_D2 LATCbits.LATC7
#define VFD_D3_TRIS TRISCbits.TRISC8
#define VFD_D3 LATCbits.LATC8
#define VFD_D4_TRIS TRISCbits.TRISC9
#define VFD_D4 LATCbits.LATC9
#define VFD_D5_TRIS TRISBbits.TRISB7
#define VFD_D5 LATBbits.LATB7
#define VFD_D6_TRIS TRISBbits.TRISB5
#define VFD_D6 LATBbits.LATB5
#define VFD_D7_TRIS TRISAbits.TRISA10
#define VFD_D7 LATAbits.LATA10

#define VFD_WRITE_TRIS TRISAbits.TRISA9
#define VFD_WRITE LATAbits.LATA9

#define VFD_DATA_COMMAND_TRIS TRISAbits.TRISA8
#define VFD_DATA_COMMAND LATAbits.LATA8

#define VFD_CHIP_SELECT_TRIS TRISAbits.TRISA7
#define VFD_CHIP_SELECT LATAbits.LATA7

#define VFD_WRITE_DATA 0
#define VFD_WRITE_COMMAND 1
//#define ENABLE_DISPLAY (CHIP_SELECT = 0)
//#define DISABLE_DISPLAY (CHIP_SELECT = 1)
//#define DO_WRITE_DATA do{WRITE = 0; Nop(); __delay_ms(1); WRITE = 1;} while(0)

#define VFD_BACKSPACE 0x08
#define VFD_ADVANCE_CURSOR 0x09
#define VFD_LINE_FEED 0x0A
#define VFD_START_BLINK 0x0B
#define VFD_STOP_BLINK 0x0C
#define VFD_CARRIAGE_RETURN 0x0D
#define VFD_NORMAL 0x11
#define VFD_OVERWRITE 0x12
#define VFD_ENABLE_HORIZONTAL_SCROLL 0x13
#define VFD_MOVE_CURSOR 0x1B
#define VFD_RESET 0x40

typedef union _vfdByte {
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
    char byte;
} vfdByte;

void vfd_init(void);

void vfd_writeCommand(const vfdByte command);
void vfd_writeDataCommand(const vfdByte data);
void vfd_writeChar(const char character);
void vfd_writeCharAtPos(const char character, const char position);
void vfd_writeString(const char string[]);
void vfd_writeStringStartingAtPosition(const char string[], vfdByte startPosition);
    
void vfd_clear(void);

#endif	/* VFD_H */
