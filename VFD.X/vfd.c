#include <xc.h>
#include <p24Fxxxx.h>

#include "config.h"
#include "vfd.h"
#include <libpic30.h>

#define SET_PIN(pin, tris, val) \
do { \
    if (val) { \
        tris = INPUT; \
        Nop(); \
    } else { \
        tris = OUTPUT; \
        Nop(); \
        pin = 0; \
    } \
}while(0)

void putDataOnPinsVfd(const vfdByte data);
void vfd_writeByte(const vfdByte data, unsigned char A0);

void vfd_init() {
    VFD_WRITE_TRIS = INPUT;
    VFD_DATA_COMMAND_TRIS = INPUT;
    VFD_CHIP_SELECT_TRIS = INPUT;
    Nop();
} 

void putDataOnPinsVfd(const vfdByte byte) {
    SET_PIN(VFD_D0, VFD_D0_TRIS, byte.bits.bit0);
    SET_PIN(VFD_D1, VFD_D1_TRIS, byte.bits.bit1);
    SET_PIN(VFD_D2, VFD_D2_TRIS, byte.bits.bit2);
    SET_PIN(VFD_D3, VFD_D3_TRIS, byte.bits.bit3);
    SET_PIN(VFD_D4, VFD_D4_TRIS, byte.bits.bit4);
    SET_PIN(VFD_D5, VFD_D5_TRIS, byte.bits.bit5);
    SET_PIN(VFD_D6, VFD_D6_TRIS, byte.bits.bit6);
    SET_PIN(VFD_D7, VFD_D7_TRIS, byte.bits.bit7);
}

void vfd_writeByte(const vfdByte data, unsigned char A0) {
    SET_PIN(VFD_DATA_COMMAND, VFD_DATA_COMMAND_TRIS, A0);
    SET_PIN(VFD_CHIP_SELECT, VFD_CHIP_SELECT_TRIS, 0);
    putDataOnPinsVfd(data);
    __delay_ms(1);
    SET_PIN(VFD_WRITE, VFD_WRITE_TRIS, 0);
    __delay_ms(1);
    SET_PIN(VFD_WRITE, VFD_WRITE_TRIS, 1);
    SET_PIN(VFD_CHIP_SELECT, VFD_CHIP_SELECT_TRIS, 1);
     __delay_ms(100);
}

void vfd_writeCommand(const vfdByte command) {
    vfd_writeByte(command, VFD_WRITE_COMMAND);
}

void vfd_writeDataCommand(const vfdByte command) {
    vfd_writeByte(command, VFD_WRITE_DATA);
}

void vfd_writeChar(const vfdByte character) {
    vfd_writeByte(character, VFD_WRITE_DATA);
}

void vfd_writeCharAtPos(const vfdByte character, vfdByte position) {
    vfd_writeCommand(position);
    vfd_writeChar(character);
}

void vfd_writeString(const vfdByte string[]) {
    unsigned int i = 0;
    for(i = 0; string[i].byte != '\0'; i++) {
        vfd_writeChar(string[i]);
    }
}

void writeStringStartingAtPositionVfd(const vfdByte string[], vfdByte startPosition) {
    vfd_writeCommand(startPosition);
    vfd_writeString(string);
}

void vfd_clear(void) {
    vfdByte lineFeed;
    lineFeed.byte = VFD_LINE_FEED;
    vfdByte carriageReturn;
    carriageReturn.byte = VFD_CARRIAGE_RETURN;
    vfd_writeDataCommand(lineFeed);
    vfd_writeDataCommand(carriageReturn);
}
