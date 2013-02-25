/*
 * File:   realTimeClock.h
 * Author: thayer.fox
 *
 * Created on February 3, 2013, 12:06 AM
 */

#ifndef REALTIMECLOCK_H
#define	REALTIMECLOCK_H

void configurePICforClock(void);
void start(void);
void stop();
void incrementClockBy1Second(void);

// HH:MM:SS
void setTime(const char* time);
void setHours(unsigned char hour);
void setMinutes(unsigned char minute);
void setSeconds(unsigned char second);
void get24HTime(char * time);
void get12HTime(char* time);
#endif	/* REALTIMECLOCK_H */

