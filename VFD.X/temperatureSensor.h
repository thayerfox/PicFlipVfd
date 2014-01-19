#ifndef TEMPERATURESENSOR_H
#define	TEMPERATURESENSOR_H

#include <xc.h>

#define CS_TRIS TRISBbits.TRISB3
#define CS_LAT LATBbits.LATB3

#define SELECT (CS_LAT = 0)
#define DESELECT (CS_LAT = 1)

void initTemperatureSensor();
signed int readTemperature();

#endif	/* TEMPERATURESENSOR_H */

