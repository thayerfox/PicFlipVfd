#include <p18f4620.h>

static unsigned char seconds = 0;
static unsigned char minutes = 0;
static unsigned char hours = 0;

void configurePICforClock(void) {
    TMR1H = 0x3C;
    TMR1L = 0xB0;

//    RCONbits.IPEN = 1;
//    RCONbits.SBOREN = 0;
//    T0CONbits.T08BIT = 0; // 16 bit timer
//    T0CONbits.T0CS = 0; // Internal instruction clock
//    T0CONbits.T0SE = 0; // Increment on rising edge
//    T0CONbits.PSA = 0; // Enable pre-scaler
//    T0CONbits.T0PS2 = 0; // Set prescaler to 128
//    T0CONbits.T0PS1 = 1;
//    T0CONbits.T0PS0 = 0;
//    INTCONbits.GIE = 1; // Enable global interrupts
//    INTCONbits.PEIE = 1; // Disable global interrupts
//    INTCONbits.TMR0IE = 1; // Enable Timer0 interrupt
//    INTCON2bits.TMR0IP = 0; ///Enable low priority interrupt Timer0
    PIR1bits.TMR1IF = 0;		// CLEAR TIMER1 INT FLAG
    PIE1bits.TMR1IE = 1;		// ENABLE TIMER 1 INTERRUPT
    IPR1bits.TMR1IP = 1;		// SET TO HIGH PRIORITY

    INTCONbits.PEIE = 1;		// ENABLE PERIPHERAL INTERRUPT
    INTCONbits.GIE = 1;			// ENABLE GLOBAL INTERRUPT

    T1CONbits.T1CKPS1 = 0;		// SET PRESCALER TO 1:1
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1OSCEN = 0;		// OSCILLATOR OFF
    T1CONbits.TMR1CS = 0;		// USE INTERNAL CLOCK
    T1CONbits.TMR1ON = 1;		// START TIMER
}

void start(void) {
//    TMR0H = 0x00;
//    TMR0L = 0x00;
//    T0CONbits.TMR0ON = 1;
}

void stop(void) {
    //T0CONbits.TMR0ON = 0;
}

void incrementClockBy1Second(void) {
    seconds++;
    if(seconds >= 60) {
        seconds = 0;
        minutes++;
        if(minutes >= 60) {
            minutes = 0;
            hours++;
            if(hours >= 24) {
                hours = 0;
            }
        }
    }
}

// HH:MM:SS
void setTime(const char* time) {
    unsigned char hours10 = time[0] - '0';
    unsigned char hours1 = time[1] - '0';
    unsigned char minutes10 = time[3] - '0';
    unsigned char minutes1 = time[4] - '0';
    unsigned char seconds10 = time[6] - '0';
    unsigned char seconds1 = time[7] - '0';

    stop();
    hours = hours10 * 10 + hours1;
    minutes = minutes10 * 10 + minutes1;
    seconds = seconds10 + seconds1;
    start();
}

void setHours(unsigned char hour) {
    hours = hour;
}

void setMinutes(unsigned char minute) {
    minutes = minute;
}

void setSeconds(unsigned char second) {
    seconds = second;
}

void get24HTime(char* time) {
    time[7] = seconds % 10 + '0';
    time[6] = seconds / 10 + '0';
    time[5] = ':';
    time[4] = minutes % 10 + '0';
    time[3] = minutes / 10 + '0';
    time[2] = ':';
    time[1] = hours % 10 + '0';
    time[0] = hours / 10 + '0';
    time[8] = '\0';
}

void get12HTime(char* time) {
    time[7] = seconds % 10 + '0';
    time[6] = seconds / 10 + '0';
    time[5] = ':';
    time[4] = minutes % 10 + '0';
    time[3] = minutes / 10 + '0';
    time[2] = ':';

    // This is ugly and needs to be fixed, but at least it has all the logic
    // and works for now.
    if(hours == 0) {
        time[0] = 1 + '0';
        time[1] = 2 + '0';
        time[8] = ' ';
        time[9] = 'A';
        time[10] = 'M';
    } else if(hours < 12) {
        time[1] = hours % 10 + '0';
        time[0] = hours / 10 + '0';
        time[8] = ' ';
        time[9] = 'A';
        time[10] = 'M';
    } else if(hours == 12) {
        time[1] = hours % 10 + '0';
        time[0] = hours / 10 + '0';
        time[8] = ' ';
        time[9] = 'P';
        time[10] = 'M';
    } else {
        unsigned char tempHours = hours - 12;
        time[1] = tempHours % 10 + '0';
        time[0] = tempHours / 10 + '0';
        time[8] = ' ';
        time[9] = 'P';
        time[10] = 'M';
    }
    time[11] = '\0';
}
