#include <xc.h>
#include <p24Fxxxx.h>

#include "config.h"
#include "vfd.h"
#include "realTimeClock.h"
#include <libpic30.h>

//static unsigned updateTime;
//static unsigned char counter;

void scrollyFunction(const vfdData **string) {
    writeString(string);
}

//_FOSC(CSW_FSCM_ON);
//_FOSCSEL(FNOSC_FRC);                    // FRC Oscillator
//_FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_NONE);
                                                                // Clock Switching is enabled and Fail Safe Clock Monitor is disabled
                                                                // OSC2 Pin Function: OSC2 Digital I/O
                                                                // Primary Oscillator Mode: Disabled
//_FWDT(FWDTEN_OFF);              // Watchdog Timer enabled/disabled by user software
                                                                // (LPRC can be disabled by clearing SWDTEN bit in RCON register
//_FICD(ICS_PGD1 & JTAGEN_OFF);   // Communication Channel: PGC1/EMUC1 and PGD1/EMUD1

// CONFIG4
#pragma config DSWDTPS = DSWDTPSF       // DSWDT Postscale Select (1:2,147,483,648 (25.7 days))
#pragma config DSWDTOSC = LPRC          // Deep Sleep Watchdog Timer Oscillator Select (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config RTCOSC = SOSC            // RTCC Reference Oscillator Select (RTCC uses Secondary Oscillator (SOSC))
#pragma config DSBOREN = OFF             // Deep Sleep BOR Enable bit (BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer (DSWDT enabled)

//// CONFIG3
#pragma config WPFP = WPFP63            // Write Protection Flash Page Segment Boundary (Highest Page (same as page 42))
#pragma config SOSCSEL = SOSC           // Secondary Oscillator Pin Mode Select (SOSC pins in Default (high drive-strength) Oscillator Mode)
#pragma config WUTSEL = LEG             // Voltage Regulator Wake-up Time Select (Default regulator start-up time used)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Last page and Flash Configuration words are unprotected)
//#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary Oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Select bit (Use default SCL1/SDA1 pins for I2C1 )
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable (Once set, the IOLOCK bit cannot be cleared)
#pragma config OSCIOFNC = ON            // OSCO Pin Configuration (OSCO pin functions as port I/O (RA3))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor (Sw Disabled, Mon Disabled)
#pragma config FNOSC = FRC              // Initial Oscillator Select (Fast RC Oscillator (FRC))
#pragma config PLL96MHZ = ON            // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled automatically on start-up)
#pragma config PLLDIV = DIV12           // USB 96 MHz PLL Prescaler Select (Oscillator input divided by 12 (48 MHz input))
#pragma config IESO = ON                // Internal External Switchover (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF              // JTAG Port Enable (JTAG port is enabled)

int main(void) {
    configurePICforVFD();
    clearDisplay();
    int i;
    vfdData data;

    TRISBbits.TRISB9 = 0;

    data.data = 'B';
    writeCharacter(&data);
    while(1) {
        LATBbits.LATB9 = 0;
        for(i = 0; i < 50; i++) {
            __delay_ms(10);
        }
       LATBbits.LATB9 = 1;
       for(i = 0; i < 50; i++) {
            __delay_ms(10);
       }
       writeCharacter(&data);
       data.data += 1;
    }
    return 0;
}

//void interrupt timer1Interupt(void) {
//    if(PIR1bits.TMR1IF) {
//        TMR1H = 0x10;
//	TMR1L += 0x00;
//        PIR1bits.TMR1IF = 0;
//        counter++;
//        if(counter >= 10) {
//            counter = 0;
//            updateTime = 1;
//        }
//    }
//}
