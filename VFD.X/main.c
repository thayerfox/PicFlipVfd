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

void scrollyFunction(const char* string) {
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
    setTime("11:59:00");
    start();
//    while(1) {
//        scrollyFunction("It Scrolls... \0");
//    }
    get24HTime(time);
    writeStringStartingAtPosition(time, 0);
    while(1) {
        if(updateTime) {
            char time[9];
            incrementClockBy1Second();
            get12HTime(time);
            writeStringStartingAtPosition(time, 0);
            updateTime = 0;
        }
    }
}

void interrupt timer1Interupt(void) {
//    if(TMR0IE && TMR0IF) {
        TMR1H = 0x90;
	TMR1L += 0x90;
        PIR1bits.TMR1IF = 0;
        counter++;
        if(counter >= 10) {
            counter = 0;
            updateTime = 1;
        }
//    }
}
