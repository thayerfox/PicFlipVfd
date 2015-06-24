#include <xc.h>
#include <p24Fxxxx.h>
#include "config.h"

#include "spi.h"
#include "w5100.h"
#include <libpic30.h>

void w5100_init(void)
{
    WIZNET_CS_TRIS = 0;
    WIZNET_CS_LAT = 1;
    __delay_us(50);
    w5100_write(WIZNET_MODE_REGISTER, 0b10000000);
    __delay_us(50);

    w5100_write(WIZNET_GATEWAY_ADDRESS + 0, 192);
    w5100_write(WIZNET_GATEWAY_ADDRESS + 1, 168);
    w5100_write(WIZNET_GATEWAY_ADDRESS + 2, 1);
    w5100_write(WIZNET_GATEWAY_ADDRESS + 3, 1);
    __delay_us(50);

    w5100_write(WIZNET_MAC_ADDRESS + 0, 0x00);
    w5100_write(WIZNET_MAC_ADDRESS + 1, 0x60);
    w5100_write(WIZNET_MAC_ADDRESS + 2, 0x78);
    w5100_write(WIZNET_MAC_ADDRESS + 3, 0x00);
    w5100_write(WIZNET_MAC_ADDRESS + 4, 0x08);
    w5100_write(WIZNET_MAC_ADDRESS + 5, 0xD2);
    __delay_us(50);

    w5100_write(WIZNET_SUBNET_MASK_ADDRESS + 0, 255);
    w5100_write(WIZNET_SUBNET_MASK_ADDRESS + 1, 255);
    w5100_write(WIZNET_SUBNET_MASK_ADDRESS + 2, 255);
    w5100_write(WIZNET_SUBNET_MASK_ADDRESS + 3, 0);
    __delay_us(50);

    w5100_write(WIZNET_IP_ADDRESS + 0, 192);
    w5100_write(WIZNET_IP_ADDRESS + 1, 168);
    w5100_write(WIZNET_IP_ADDRESS + 2, 1);
    w5100_write(WIZNET_IP_ADDRESS + 3, 56);
    __delay_us(50);

    w5100_write(WIZNET_RX_REGISTER, 0x55);
    w5100_write(WIZNET_TX_REGISTER, 0x55);
    __delay_us(50);
}

void w5100_write(unsigned int address, unsigned char data)
{
    unsigned char rx = 0xFF;

    WIZNET_CS_LAT = 0;
    rx = writeSpi(WIZNET_WRITE_OPCODE);
    rx = writeSpi((address & 0xFF00) >> 8);
    rx = writeSpi(address & 0xFF);
    rx = writeSpi(data);
    WIZNET_CS_LAT = 1;
}

unsigned char w5100_read(unsigned int addr)
{
    unsigned char data = 0xFF;

    WIZNET_CS_LAT = 0;
    data = writeSpi(WIZNET_READ_OPCODE);
    data = writeSpi(addr >> 8);  // Send address msb
    data = writeSpi(addr);       // Send address lsb
    data = writeSpi(0);          // Read data from W5100
    WIZNET_CS_LAT = 1;
    return data;
}
