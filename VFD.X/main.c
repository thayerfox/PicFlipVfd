#include <xc.h>
#include <p24Fxxxx.h>

#include "config.h"
#include "vfd.h"
//#include "realTimeClock.h"
#include "spi.h"
#include "FSIO.h"
#include "w5100.h"
#include <libpic30.h>
#include "FSIO.h"
#include "webserver.h"

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

int main(void) {
    unsigned int i;
    FSFILE *file;
    char str[10] = "\0\0\0\0\0\0\0\0\0\0";

    TRISBbits.TRISB8 = 0;

    // Delay 5s to allow VFD to power up
    for(i = 0; i < 50; i++) {
        __delay_ms(100);
        LATBbits.LATB8 ^= 1;
    }

    initSPI();
    initW5100();
    vfd_init();
    FSInit();
    vfd_clear();

    vfd_writeString("Noritake Itron JAPAN\0");

    vfd_clear();
    file = FSfopen("vfd.txt", "r");
    FSfread(str, sizeof(char), 10, file);

    vfd_writeString(str);
    FSfclose(file);

    while(1) {
        testserver();
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
