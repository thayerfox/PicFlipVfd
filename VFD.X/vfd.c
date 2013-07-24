#include <xc.h>

#include "config.h"
#include "vfd.h"
#include <libpic30.h>

void putDataOnPins(const vfdData *data);

void configurePICforVFD() {
//    WRITE_TRIS = OUTPUT;
//    DATA_COMMAND_TRIS = OUTPUT;
//    CHIP_SELECT_TRIS = OUTPUT;
//
//    D0_TRIS = OUTPUT;
//    D1_TRIS = OUTPUT;
//    D2_TRIS = OUTPUT;
//    D3_TRIS = OUTPUT;
//    D4_TRIS = OUTPUT;
//    D5_TRIS = OUTPUT;
//    D6_TRIS = OUTPUT;
//    D7_TRIS = OUTPUT;
//
//    WRITE = 1;
//    DATA_COMMAND = 1;
//    CHIP_SELECT = 1;

    WRITE_TRIS = INPUT;
    DATA_COMMAND_TRIS = INPUT;
    CHIP_SELECT_TRIS = INPUT;

    Nop();
} 

//void setPin(char theBit) {
//    if(theBit) {
//        theTris = INPUT;
//    } else {
//        theTris = OUTPUT;
//        Nop();
//        theBit = 0;
//    }
//}

void putDataOnPins(const vfdData* data) {
    if (data->bits.bit0) {
        D0_TRIS = INPUT;
        Nop();
    } else {
        D0_TRIS = OUTPUT;
        Nop();
        D0 = 0;
    }

    if(data->bits.bit1) {
        D1_TRIS = INPUT;
        Nop();
    } else {
        D1_TRIS = OUTPUT;
        Nop();
        D1 = 0;
    }
    if(data->bits.bit2) {
        D2_TRIS = INPUT;
        Nop();
    } else {
        D2_TRIS = OUTPUT;
        Nop();
        D2 = 0;
    }

    if(data->bits.bit3) {
        D3_TRIS = INPUT;
        Nop();
    } else {
        D3_TRIS = OUTPUT;
        Nop();
        D3 = 0;
    }

    if(data->bits.bit4) {
        D4_TRIS = INPUT;
        Nop();
    } else {
        D4_TRIS = OUTPUT;
        Nop();
        D4 = 0;
    }

    if(data->bits.bit5) {
        D5_TRIS = INPUT;
        Nop();
    } else {
        D5_TRIS = OUTPUT;
        Nop();
        D5 = 0;
    }
    if(data->bits.bit6) {
        D6_TRIS = INPUT;
        Nop();
    } else {
        D6_TRIS = OUTPUT;
        Nop();
        D6 = 0;
    }

    if(data->bits.bit7) {
        D7_TRIS = INPUT;
        Nop();
    } else {
        D7_TRIS = OUTPUT;
        Nop();
        D7 = 0;
    }

//    D0 = data->bits.bit7;
//    D1 = data->bits.bit6;
//    D2 = data->bits.bit5;
//    D3 = data->bits.bit4;
//    D4 = data->bits.bit3;
//    D5 = data->bits.bit2;
//    D6 = data->bits.bit1;
//    D7 = data->bits.bit0;
}

void write(const vfdData* data, unsigned char A0) {
    DATA_COMMAND = A0;
    if(A0) {
        DATA_COMMAND_TRIS = INPUT;
        Nop();
    } else {
        DATA_COMMAND_TRIS = OUTPUT;
        Nop();
        DATA_COMMAND = 0;
    }
    
//    ENABLE_DISPLAY;
    CHIP_SELECT_TRIS = OUTPUT;
    Nop();
    CHIP_SELECT = 0;
__delay_ms(1);
    putDataOnPins(data);
    __delay_ms(1);
//    DO_WRITE_DATA;
//    WRITE = 0;
    WRITE_TRIS = OUTPUT;
    Nop();
    WRITE = 0;
    Nop();

    __delay_ms(1);

//    WRITE = 1;
    WRITE_TRIS = INPUT;
    Nop();

//    DISABLE_DISPLAY;
    CHIP_SELECT_TRIS = INPUT;
    Nop();
    

//    for(j = 0; j < 10; j++) {
//        for(i = 0; i < 65525; i++) {
//            Nop();
//        }
//    }
     __delay_ms(100);
     __delay_ms(100);
}

void writeCommand(const vfdData *command) {
    write(command, WRITE_COMMAND);
}

void writeDataCommand(const vfdData *command) {
    write(command, WRITE_DATA);
}

void writeCharacter(const vfdData *character) {
    write(character, WRITE_DATA);
}

void writeCharacterAtPosition(const vfdData *character, vfdData *position) {
    writeCommand(position);
    writeCharacter(character);
}

void writeString(const vfdData **string) {
    unsigned int i = 0;
    for(i = 0; string[i]->data != '\0'; i++) {
        writeCharacter(string[i]);
    }
}

void writeStringStartingAtPosition(const vfdData **string, vfdData *startPosition) {
    writeCommand(startPosition);
    writeString(string);
}

void clearDisplay(void) {
    vfdData lineFeed;
    lineFeed.data = LINE_FEED;
    vfdData carriageReturn;
    carriageReturn.data = CARRIAGE_RETURN;
    writeDataCommand(&lineFeed);
    writeDataCommand(&carriageReturn);
}
