/*
 * File:   main.c
 * Author: Bananas
 *
 * Created on February 2, 2013, 3:26 PM
 */

#include <p18f4620.h>
#include <delays.h>

#include "vfd.h"
#include "realTimeClock.h"

static unsigned updateTime;
static unsigned char counter;

void scrollyFunction(rom const char* string) {
    unsigned char character = string[0];
    unsigned char i = 0;


    while(character != '\0') {
        writeCharacter(character);
        i++;
        character = string[i];
        Delay10KTCYx(60);
    }
}

void main(void) {
    char time[9];
    TRISA = 0;
    counter = 0;
    updateTime = 0;
    configurePICforVFD();
    configurePICforClock();

    clearDisplay();
    writeDataCommand(ENABLE_HORIZONTAL_SCROLL);
    while(1) {
        scrollyFunction("It Scrolls... \0");
    }
//    start();
//    setRomTime("00:00:00");
//    getTime(time);
//    writeStringStartingAtPosition(time, 0);
//    while(1) {
//        if(updateTime) {
//            char time[9];
//            incrementClockBy1Second();
//            getTime(time);
//            writeStringStartingAtPosition(time, 0);
//            updateTime = 0;
//        }
//    }
}

void ISR (void)
{
    //writeCharacter('B' + counter);
//    PIR1bits.TMR1IF = 0;
//    TMR1H = 0xFF;
//    TMR1L = 0xF1;
//    counter++;
//    if(counter >= 10) {
//        counter = 0;
//        updateTime = 1;
//    }
}

#pragma code lowvector=0x18
void lowvector(void)
{

_asm goto ISR _endasm
}
#pragma code

#pragma code highvector=0x08
void highvector(void)
{

_asm goto ISR _endasm
}
#pragma code
