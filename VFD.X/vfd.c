#include <p18f4620.h>
#include <delays.h>

#include "vfd.h"

void configurePICforVFD() {
    DATA_TRIS = PORT_OUTPUT;
    WRITE_TRIS = OUTPUT;
    DATA_COMMAND_TRIS = OUTPUT;
    READ_TRIS = OUTPUT;
    CHIP_SELECT_TRIS = OUTPUT;
    BUSY_TRIS = INPUT;

    WRITE = 1;
    DATA_COMMAND = 1;
    READ = 1;
    CHIP_SELECT = 1;
   
    Nop();
}

void write(auto char data, unsigned char A0) {
    DATA_COMMAND = A0;
    ENABLE_DISPLAY;
    DATA = data;
    WRITE = 0;
    Nop();
    WRITE = 1;
    DISABLE_DISPLAY;
    // Tuned for 20MHz Pic 18f4620 time = 50ns * 4 * 80 = 16ms
    Delay10TCYx(80);
}

void writeCommand(auto unsigned char command) {
    write(command, WRITE_COMMAND);
}

void writeDataCommand(auto char command) {
    write(command, WRITE_DATA);
}

void writeCharacter(auto char character) {
    write(character, WRITE_DATA);
}

void writeCharacterAtPosition(auto char character, unsigned char position) {
    writeCommand(position);
    write(character, WRITE_DATA);
}

void writeString(auto char* string) {
    unsigned char character = string[0];
    unsigned char i = 0;

    while(character != '\0') {
        write(character, 0);
        i++;
        character = string[i];
    }
}

void writeRomString(const rom char * string) {
    unsigned char character = string[0];
    unsigned char i = 0;

    while(character != '\0') {
        write(character, 0);
        i++;
        character = string[i];
    }
}

void writeStringStartingAtPosition(auto char* string, unsigned char startPosition) {
    unsigned char character = string[0];
    unsigned char i = 0;

    writeCommand(startPosition);

    while(character != '\0') {
        write(character, 0);
        i++;
        character = string[i];
    }
}

void writeRomStringStartingAtPosition(const rom char * string, unsigned char startPosition) {
    unsigned char character = string[0];
    unsigned char i = 0;

    writeCommand(startPosition);

    while(character != '\0') {
        write(character, 0);
        i++;
        character = string[i];
    }
}

void clearDisplay(void) {
    writeDataCommand(LINE_FEED);
    writeDataCommand(CARRIAGE_RETURN);
}
