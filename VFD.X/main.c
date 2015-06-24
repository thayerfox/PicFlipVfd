#include <xc.h>
#include <p24Fxxxx.h>

#include "config.h"
#include "vfd.h"
#include "spi.h"
#include "FSIO.h"
#include "w5100.h"
#include "webserver.h"

#include <libpic30.h>

//#define ENABLE_VFD
//#define ENABLE_SD
#define ENABLE_WIZNET

_CONFIG1(WDTPS_PS1
  & FWPSA_PR32
  & WINDIS_OFF
  & FWDTEN_OFF
  & ICS_PGx1 //emulatore su pgec3/pged3
  & GWRP_OFF
  & GCP_OFF
  & JTAGEN_OFF)
 _CONFIG2(POSCMOD_NONE //primary disabled
  & I2C1SEL_PRI
  & IOL1WAY_OFF
  & OSCIOFNC_OFF//I/O su RA3
  & FCKSM_CSDCMD
  & FNOSC_FRCPLL  //FRC+PLL
  & PLL96MHZ_ON
  & PLLDIV_NODIV //4M input
  & IESO_ON)
 _CONFIG3(WPFP_WPFP0
  & SOSCSEL_IO  //RA4/RB4 I/O
  & WUTSEL_LEG
  & WPDIS_WPDIS
  & WPCFG_WPCFGDIS
  & WPEND_WPENDMEM)
 _CONFIG4(DSWDTPS_DSWDTPS3
  & DSWDTOSC_LPRC
  & RTCOSC_SOSC
  & DSBOREN_OFF
  & DSWDTEN_OFF)

int main(void)
{
    unsigned int i;
    FSFILE *readFile;
    FSFILE *writeFile;
    char str[10] = "\0\0\0\0\0\0\0\0\0\0";

    TRISBbits.TRISB8 = 0;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;

    // Delay to allow VFD to power up
    for(i = 0; i < 5; i++)
    {
        __delay_ms(100);
        LATBbits.LATB8 ^= 1;
    }
    LATBbits.LATB8 = 0;
#if defined (ENABLE_SD) || defined (ENABLE_WIZNET)
    initSPI();
#endif
#ifdef ENABLE_WIZNET
    w5100_init();
#endif
#ifdef ENABLE_VFD
    vfd_init();
    vfd_clear();
    vfd_writeString("Noritake Itron JAPAN\0");
    vfd_clear();
#endif
#ifdef ENABLE_SD
    int initSuccess = FSInit();
    if (initSuccess != 0)
    {
#ifdef ENABLE_VFD
        vfd_clear();
        vfd_writeString("Fail FS Init\0");
#endif
        LATAbits.LATA0 = 1;
    }
    readFile = FSfopen("read.txt", "r");
    if (readFile == NULL)
    {
#ifdef ENABLE_VFD
        vfd_clear();
        vfd_writeString("Fail FS Open\0");
#endif
        LATAbits.LATA0 = 1;
    }
    FSfread(str, sizeof(char), 10, readFile);
    writeFile = FSfopen("write.txt", "w");
    if (writeFile == NULL)
    {
#ifdef ENABLE_VFD
        vfd_clear();
        vfd_writeString("Fail FS Open\0");
#endif
        LATAbits.LATA1 = 1;
    }
    FSfwrite(str, sizeof(char), 10, writeFile);
#ifdef ENABLE_VFD
    vfd_writeString(str);
#endif
    FSfclose(readFile);
    FSfclose(writeFile);
#endif
    while(1) {
        LATAbits.LATA0 ^= 1;
#ifdef ENABLE_WIZNET
        testserver();
#endif
    }
    return 0;
}

//void _ISR _T1Interrupt(void)
//{
//    IEC0BITS.T1IE = 1;
//    T1CONBITS.TON = 1;
//    T1CONBITS.TCKPS = 0b00;
//}
