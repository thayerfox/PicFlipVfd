#include <xc.h>
#include <p24Fxxxx.h>
#include "config.h"

#include "spi.h"
#include "w5100.h"
#include <libpic30.h>

void initW5100(void) {
    WIZNET_CS_TRIS = 0;
    WIZNET_CS_LAT = 1;
    __delay_us(50);
    writeWiznet(WIZNET_MODE_REGISTER, 0b10000000);
    __delay_us(50);

    writeWiznet(WIZNET_GATEWAY_ADDRESS + 0, 192);
    writeWiznet(WIZNET_GATEWAY_ADDRESS + 1, 168);
    writeWiznet(WIZNET_GATEWAY_ADDRESS + 2, 1);
    writeWiznet(WIZNET_GATEWAY_ADDRESS + 3, 1);
    __delay_us(50);

    writeWiznet(WIZNET_MAC_ADDRESS + 0, 0x00);
    writeWiznet(WIZNET_MAC_ADDRESS + 1, 0x60);
    writeWiznet(WIZNET_MAC_ADDRESS + 2, 0x78);
    writeWiznet(WIZNET_MAC_ADDRESS + 3, 0x00);
    writeWiznet(WIZNET_MAC_ADDRESS + 4, 0x08);
    writeWiznet(WIZNET_MAC_ADDRESS + 5, 0xD2);
    __delay_us(50);

    writeWiznet(WIZNET_SUBNET_MASK_ADDRESS + 0, 255);
    writeWiznet(WIZNET_SUBNET_MASK_ADDRESS + 1, 255);
    writeWiznet(WIZNET_SUBNET_MASK_ADDRESS + 2, 255);
    writeWiznet(WIZNET_SUBNET_MASK_ADDRESS + 3, 0);
    __delay_us(50);

    writeWiznet(WIZNET_IP_ADDRESS + 0, 192);
    writeWiznet(WIZNET_IP_ADDRESS + 1, 168);
    writeWiznet(WIZNET_IP_ADDRESS + 2, 1);
    writeWiznet(WIZNET_IP_ADDRESS + 3, 56);
    __delay_us(50);

    writeWiznet(WIZNET_RX_REGISTER, 0x55);
    writeWiznet(WIZNET_TX_REGISTER, 0x55);
    __delay_us(50);
}

void writeWiznet(unsigned int address, unsigned char data) {
    unsigned char rx = 0xFF;

    WIZNET_CS_LAT = 0;
    rx = writeSpi(WIZNET_WRITE_OPCODE);
    rx = writeSpi((address & 0xFF00) >> 8);
    rx = writeSpi(address & 0xFF);
    rx = writeSpi(data);
    WIZNET_CS_LAT = 1;
}

unsigned char readWiznet(unsigned int addr) {
    unsigned char data = 0xFF;

    WIZNET_CS_LAT = 0;
    data = writeSpi(WIZNET_READ_OPCODE);
    data = writeSpi(addr >> 8);  // Send address msb
    data = writeSpi(addr);       // Send address lsb
    data = writeSpi(0);          // Read data from W5100
    WIZNET_CS_LAT = 1;
    return data;
}
