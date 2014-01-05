#include <p24Fxxxx.h>

#include "spi.h"

void initSPI(void) {

    AD1PCFGbits.PCFG8 = 1;
    AD1PCFGbits.PCFG7 = 1;
    AD1PCFGbits.PCFG6 = 1;
    
    TRISCbits.TRISC2 = 1;

    RPINR20bits.SDI1R = 18;     // Assign SDI1 to RP18 / Pin 27 / RC2
    RPOR8bits.RP17R = 0b00111;  // Assign SDO1 to RP17 / Pin 26 / RC1
    RPOR10bits.RP20R = 0b01000; // Assign SCK1 to RP20 / Pin 37 / RC4
    RPOR11bits.RP22R = 9;        

    SPI1CON1bits.DISSCK = 0;
    SPI1CON1bits.DISSDO = 0;
    SPI1CON1bits.MODE16 = 0; // 8-bit mode
    SPI1CON1bits.SMP = 0;
    SPI1CON1bits.CKE = 1;
    SPI1CON1bits.SSEN = 1;
    SPI1CON1bits.CKP = 0;
    SPI1CON1bits.MSTEN = 1;
    SPI1CON1bits.SPRE = 0b110;
    SPI1CON1bits.PPRE = 0b10;
    SPI1BUF = 0x00;

    SPI1CON2bits.FRMEN = 0;
    SPI1CON2bits.SPIFSD = 0;

    IPC2bits.SPI1IP = 0b000; // The lowest of tehs prioritahs.
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN = 1;

    IFS0bits.SPI1IF = 0;
    IEC0bits.SPF1IE = 1;
}

unsigned char writeSpi(unsigned char data) {
    SPI1BUF = data;
    Nop();
    while (SPI1STATbits.SPITBF || !SPI1STATbits.SPIRBF);
    Nop();
    return SPI1BUF;
}
