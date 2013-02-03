#include <p18f4620.h>

static unsigned char seconds = 0;
static unsigned char minutes = 0;
static unsigned char hours = 0;

void configurePICforClock(void) {
    RCONbits.IPEN = 1;
    RCONbits.SBOREN = 0;
    T0CONbits.T08BIT = 0; // 16 bit timer
    T0CONbits.T0CS = 0; // Internal instruction clock
    T0CONbits.T0SE = 0; // Increment on rising edge
    T0CONbits.PSA = 0; // Enable pre-scaler
    T0CONbits.T0PS2 = 0; // Set prescaler to 128
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 0;
    INTCONbits.GIE = 1; // Enable global interrupts
    INTCONbits.PEIE = 1; // Disable global interrupts
    INTCONbits.TMR0IE = 1; // Enable Timer0 interrupt
    INTCON2bits.TMR0IP = 0; ///Enable low priority interrupt Timer0
}

void start(void) {
    TMR0H = 0x00;
    TMR0L = 0x00;
    T0CONbits.TMR0ON = 1;
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
void setTime(auto char* time) {
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

void setRomTime(const rom char* time) {
    unsigned char seconds1 = time[7] - '0';
    unsigned char seconds10 = time[6] - '0';
    unsigned char minutes1 = time[4] - '0';
    unsigned char minutes10 = time[3] - '0';
    unsigned char hours1 = time[1] - '0';
    unsigned char hours10 = time[0] - '0';

    hours = hours10 * 10 + hours1;
    minutes = minutes10 * 10 + minutes1;
    seconds = seconds10 * 10 + seconds1;
}

void setHours(auto unsigned char hour) {
    hours = hour;
}

void setMinutes(auto unsigned char minute) {
    minutes = minute;
}

void setSeconds(auto unsigned char second) {
    seconds = second;
}

void getTime(auto char* time) {
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
