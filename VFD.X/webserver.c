#include <xc.h>
#include <p24Fxxxx.h>
#include <string.h>
#include "config.h"
#include <libpic30.h>
#include "w5100.h"
#include "webserver.h"


unsigned char OpenSocket(unsigned char sock, unsigned char eth_protocol, unsigned int tcp_port);
void CloseSocket(unsigned char sock);
void DisconnectSocket(unsigned char sock);
unsigned char Listen(unsigned char sock);
unsigned char Send(unsigned char sock, const unsigned char *buf, unsigned int buflen);
unsigned int Receive(unsigned char sock, unsigned char *buf, unsigned int buflen);
unsigned int ReceivedSize(unsigned char sock);

#define  MAX_BUF					512			/* largest buffer we can read from chip */

#define  HTTP_PORT					80			/* TCP port for HTTP */

unsigned char buf[MAX_BUF];

unsigned char OpenSocket(unsigned char sock, unsigned char eth_protocol, unsigned int tcp_port) {
    unsigned char retval;
    unsigned int sockaddr;

    retval = W5100_FAIL; // assume this doesn't work
    if (sock >= W5100_NUM_SOCKETS) return retval; // illegal socket value is bad!

    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket

    if (readWiznet(sockaddr + W5100_SR_OFFSET) == W5100_SKT_SR_CLOSED) // Make sure we close the socket first
    {
        CloseSocket(sock);
    }

    writeWiznet(sockaddr + W5100_MR_OFFSET, eth_protocol); // set protocol for this socket
    writeWiznet(sockaddr + W5100_PORT_OFFSET, ((tcp_port & 0xFF00) >> 8)); // set port for this socket (MSB)
    writeWiznet(sockaddr + W5100_PORT_OFFSET + 1, (tcp_port & 0x00FF)); // set port for this socket (LSB)
    writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_OPEN); // open the socket

    while (readWiznet(sockaddr + W5100_CR_OFFSET)); // loop until device reports socket is open (blocks!!)

    if (readWiznet(sockaddr + W5100_SR_OFFSET) == W5100_SKT_SR_INIT) retval = sock; // if success, return socket number
    else CloseSocket(sock); // if failed, close socket immediately

    return retval;
}

void CloseSocket(unsigned char sock) {
    unsigned int sockaddr;

    if (sock > W5100_NUM_SOCKETS) return; // if illegal socket number, ignore request
    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket

    writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_CLOSE); // tell chip to close the socket
    while (readWiznet(sockaddr + W5100_CR_OFFSET)); // loop until socket is closed (blocks!!)
}

void DisconnectSocket(unsigned char sock) {
    unsigned int sockaddr;

    if (sock > W5100_NUM_SOCKETS) return; // if illegal socket number, ignore request
    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket

    writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_DISCON); // disconnect the socket
    while (readWiznet(sockaddr + W5100_CR_OFFSET)); // loop until socket is closed (blocks!!)
}

unsigned char Listen(unsigned char sock) {
    unsigned char retval;
    unsigned int sockaddr;

    retval = W5100_FAIL; // assume this fails
    if (sock > W5100_NUM_SOCKETS) return retval; // if illegal socket number, ignore request

    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket
    if (readWiznet(sockaddr + W5100_SR_OFFSET) == W5100_SKT_SR_INIT) // if socket is in initialized state...
    {
        writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_LISTEN); // put socket in listen state
        while (readWiznet(sockaddr + W5100_CR_OFFSET)); // block until command is accepted

        if (readWiznet(sockaddr + W5100_SR_OFFSET) == W5100_SKT_SR_LISTEN) retval = W5100_OK; // if socket state changed, show success
        else CloseSocket(sock); // not in listen mode, close and show an error occurred
    }
    return retval;
}

unsigned char Send(unsigned char sock, const unsigned char *buf, unsigned int buflen) {
    unsigned int ptr;
    unsigned int offaddr;
    unsigned int realaddr;
    unsigned int txsize;
    unsigned int timeout;
    unsigned int sockaddr;

    if (buflen == 0 || sock >= W5100_NUM_SOCKETS) return W5100_FAIL; // ignore illegal requests
    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket
    // Make sure the TX Free Size Register is available
    txsize = readWiznet(sockaddr + W5100_TX_FSR_OFFSET); // make sure the TX free-size reg is available
    txsize = (((txsize & 0x00FF) << 8) + readWiznet(sockaddr + W5100_TX_FSR_OFFSET + 1));

    timeout = 0;
    while (txsize < buflen) {
        __delay_ms(1);

        txsize = readWiznet(sockaddr + W5100_TX_FSR_OFFSET); // make sure the TX free-size reg is available
        txsize = (((txsize & 0x00FF) << 8) + readWiznet(sockaddr + W5100_TX_FSR_OFFSET + 1));

        if (timeout++ > 1000) // if max delay has passed...
        {
            DisconnectSocket(sock); // can't connect, close it down
            return W5100_FAIL; // show failure
        }
    }

    // Read the Tx Write Pointer
    ptr = readWiznet(sockaddr + W5100_TX_WR_OFFSET);
    offaddr = (((ptr & 0x00FF) << 8) + readWiznet(sockaddr + W5100_TX_WR_OFFSET + 1));

    while (buflen) {
        buflen--;
        realaddr = W5100_TXBUFADDR + (offaddr & W5100_TX_BUF_MASK); // calc W5100 physical buffer addr for this socket

        writeWiznet(realaddr, *buf); // send a byte of application data to TX buffer
        offaddr++; // next TX buffer addr
        buf++; // next input buffer addr
    }

    writeWiznet(sockaddr + W5100_TX_WR_OFFSET, (offaddr & 0xFF00) >> 8); // send MSB of new write-pointer addr
    writeWiznet(sockaddr + W5100_TX_WR_OFFSET + 1, (offaddr & 0x00FF)); // send LSB

    writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_SEND); // start the send on its way
    while (readWiznet(sockaddr + W5100_CR_OFFSET)); // loop until socket starts the send (blocks!!)

    return W5100_OK;
}

/*
 *  Define macros for selecting and deselecting the W5100 device.
 */
#define W51_ENABLE (WIZNET_CS_LAT = 1)
#define W51_DISABLE (WIZNET_CS_LAT = 0)

unsigned int Receive(unsigned char sock, unsigned char *buf, unsigned int buflen) {
    unsigned int ptr;
    unsigned int offaddr;
    unsigned int realaddr;
    unsigned int sockaddr;

    if (buflen == 0 || sock >= W5100_NUM_SOCKETS) return W5100_FAIL; // ignore illegal conditions

    if (buflen > (MAX_BUF - 2)) buflen = MAX_BUF - 2; // requests that exceed the max are truncated

    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket
    ptr = readWiznet(sockaddr + W5100_RX_RD_OFFSET); // get the RX read pointer (MSB)
    offaddr = (((ptr & 0x00FF) << 8) + readWiznet(sockaddr + W5100_RX_RD_OFFSET + 1)); // get LSB and calc offset addr

    while (buflen) {
        buflen--;
        realaddr = W5100_RXBUFADDR + (offaddr & W5100_RX_BUF_MASK);
        *buf = readWiznet(realaddr);
        offaddr++;
        buf++;
    }
    *buf = '\0'; // buffer read is complete, terminate the string

    // Increase the S0_RX_RD value, so it point to the next receive
    writeWiznet(sockaddr + W5100_RX_RD_OFFSET, (offaddr & 0xFF00) >> 8); // update RX read offset (MSB)
    writeWiznet(sockaddr + W5100_RX_RD_OFFSET + 1, (offaddr & 0x00FF)); // update LSB

    // Now Send the RECV command
    writeWiznet(sockaddr + W5100_CR_OFFSET, W5100_SKT_CR_RECV); // issue the receive command
    __delay_us(5); // wait for receive to start

    return W5100_OK;
}

unsigned int ReceivedSize(unsigned char sock) {
    unsigned int val;
    unsigned int sockaddr;

    if (sock >= W5100_NUM_SOCKETS) return 0;
    sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket
    val = readWiznet(sockaddr + W5100_RX_RSR_OFFSET) & 0xff;
    val = (val << 8) + readWiznet(sockaddr + W5100_RX_RSR_OFFSET + 1);
    return val;
}

int testserver(void) {
    unsigned int sockaddr;
    unsigned char mysocket;
    unsigned int rsize;


    mysocket = 0; // magic number! declare the socket number we will use (0-3)
    sockaddr = W5100_SKT_BASE(mysocket); // calc address of W5100 register set for this socket

    /*
     *  The main loop.  Control stays in this loop forever, processing any received packets
     *  and sending any requested data.
     */
    while (1) {
        switch (readWiznet(sockaddr + W5100_SR_OFFSET)) // based on current status of socket...
        {
            case W5100_SKT_SR_CLOSED: // if socket is closed...
                LATBbits.LATB8 = 0;
                if (OpenSocket(mysocket, W5100_SKT_MR_TCP, HTTP_PORT) == mysocket) // if successful opening a socket...
                {
                    Listen(mysocket);
                    __delay_ms(1);
                }
                break;

            case W5100_SKT_SR_ESTABLISHED: // if socket connection is established...
                LATBbits.LATB8 = 1;
                rsize = ReceivedSize(mysocket); // find out how many bytes
                if (rsize > 0) {
                    if (Receive(mysocket, buf, rsize) != W5100_OK) break; // if we had problems, all done
                    /*
                     *  Add code here to process the payload from the packet.
                     *
                     *  For now, we just ignore the payload and send a canned HTML page so the client at least
                     *  knows we are alive.
                     */
                    strcpy((char *) buf, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
                    strcat((char *) buf, "<html>\r\n<body>\r\n");
                    strcat((char *) buf, "<title>Karl's W5100 web server (ATmega644p)</title>\r\n");
                    strcat((char *) buf, "<h2>Karl's ATmega644p web server using Wiznet W5100 chip</h2>\r\n");
                    strcat((char *) buf, "<br /><hr>\r\n");
                    if (Send(mysocket, buf, strlen((char *) buf)) == W5100_FAIL) break; // just throw out the packet for now

                    strcpy((char *) buf, "This is part 2 of the page.");
                    strcat((char *) buf, "</body>\r\n</html>\r\n");
                    if (Send(mysocket, buf, strlen((char *) buf)) == W5100_FAIL) break; // just throw out the packet for now

                    DisconnectSocket(mysocket);
                } else // no data yet...
                {
                    __delay_us(10);
                }
                break;

            case W5100_SKT_SR_FIN_WAIT:
            case W5100_SKT_SR_CLOSING:
            case W5100_SKT_SR_TIME_WAIT:
            case W5100_SKT_SR_CLOSE_WAIT:
            case W5100_SKT_SR_LAST_ACK:
                CloseSocket(mysocket);
                break;
        }
    }

    return 0;
}







