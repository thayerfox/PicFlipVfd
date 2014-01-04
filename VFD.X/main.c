#include <xc.h>
#include <p24Fxxxx.h>

#include "config.h"
#include "vfd.h"
//#include "realTimeClock.h"
#include "spi.h"
//#include "w5100.h"
#include <libpic30.h>
//#include "FSIO.h"
//#include "webserver.h"

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
  & PLLDIV_DIV2 //4M input
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
    TRISBbits.TRISB8 = 0;
//    unsigned int j = 0;
//    while (1) {
//        LATBbits.LATB8 ^= 1;
//        for (j = 0; j < 65535; j++) {
//            Nop();
//        }
//        for (j = 0; j < 65535; j++) {
//            Nop();
//        }
//    }
    vfd_init();
//    initSPI();
//    initW5100();
    vfd_clear();
//    int i;
//    FSFILE *testFile;
    vfdByte vfdData[20];
//    char data[20];

//    TRISBbits.TRISB7 = 0;

//    for(i = 0; i < 1; i++) {
//        __delay_us(10);
//    }

//    int a = FSInit();
//    testFile = FSfopen("vfd.txt", "r");
//    int b = FSfread((void *)data, 10, 1, testFile);
//    FSfclose(testFile);

//    for (i = 0; i < 10; i++) {
//        vfdData[i].byte = data[i];
//    }
//
    vfdData[10].byte = '\0';
    vfd_writeString(vfdData);
    vfdData[0].byte = 'a';
    vfdData[1].byte = 'b';
    vfdData[2].byte = 'v';
    vfdData[3].byte = 'd';
    vfdData[4].byte = 'e';
    vfdData[5].byte = 'f';
    vfdData[6].byte = 'g';
    vfdData[7].byte = 'h';
    vfdData[8].byte = 'i';
    vfdData[9].byte = 'j';
    vfdData[10].byte = '\0';
//    char asd = 'D';
//    vfd_writeChar((vfdByte)asd);
    
//    unsigned char val = readWiznet(WIZNET_IP_ADDRESS);
//    if (val == 192) {
//        data.data = '1';
////        writeCharacterVfd(&data);
//    } else {
//        data.data = '0';
////        writeCharacterVfd(&data);
//    }

//    for(i = 0; i < 1; i++) {
//            __delay_us(10);
//    }

//    writeWiznet(0, 0x80);

//    vfdByte d;
//    testserver();
//    U1CONbits.USBEN = 0;
    char c = 'a';
    while(1) {
        int i = 0;
        LATBbits.LATB8 = 0;
        for(i = 0; i < 50; i++) {
            __delay_ms(40);
        }
        c += (i % 26);
//        vfd_writeChar((vfdByte)c);
        LATBbits.LATB8 = 1;
//       d.byte = readWiznet(WIZNET_GATEWAY_ADDRESS);

//       if (d.byte == 192) {
//           d.byte = '1';
//            vfd_writeChar(d);
//       } else {
//           d.byte = '0';
//           vfd_writeChar(d);
//       }
       
       for(i = 0; i < 50; i++) {
            __delay_ms(40);
       }
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
