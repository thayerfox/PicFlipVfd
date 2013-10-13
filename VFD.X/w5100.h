#ifndef W5100_H
#define	W5100_H

#define WIZNET_CS_TRIS TRISCbits.TRISC3 // pin 36
#define WIZNET_CS_PORT PORTCbits.RC3
#define WIZNET_CS_LAT LATCbits.LATC3

#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

#define WIZNET_MODE_REGISTER   0x0000   // Mode Register
#define WIZNET_GATEWAY_ADDRESS  0x0001   // Gateway Address: 0x0001 to 0x0004
#define WIZNET_SUBNET_MASK_ADDRESS 0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define WIZNET_MAC_ADDRESS  0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define WIZNET_IP_ADDRESS 0x000F   // Source IP Address: 0x000F to 0x0012
#define WIZNET_RX_REGISTER 0x001A   // RX Memory Size Register
#define WIZNET_TX_REGISTER 0x001B   // TX Memory Size Register

void initW5100(void);
void writeWiznet(unsigned int address, unsigned char data);
unsigned char readWiznet(unsigned int addr);

#endif	/* W5100_H */
