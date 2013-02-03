/*
 * File:   realTimeClock.h
 * Author: thayer.fox
 *
 * Created on February 3, 2013, 12:06 AM
 */

#ifndef REALTIMECLOCK_H
#define	REALTIMECLOCK_H


static unsigned char seconds = 0;
static unsigned char minutes = 0;
static unsigned char hours = 0;

void configurePICforClock(void);
void start(void);
void stop();
void incrementClockBy1Second(void);

// HH:MM:SS
void setTime(auto char* time);
void setRomTime(rom const char* time);
void setHours(auto unsigned char hour);
void setMinutes(auto unsigned char minute);
void setSeconds(auto unsigned char second);
void getTime(auto char * time);
#endif	/* REALTIMECLOCK_H */

