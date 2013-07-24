#ifndef REALTIMECLOCK_H
#define	REALTIMECLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

void configurePICforClock(void);
void start(void);
void stop();
void incrementClockBy1Second(void);

void setTime(const char* HH_MM_SS);
void setHours(unsigned char hour);
void setMinutes(unsigned char minute);
void setSeconds(unsigned char second);
void get24HTime(char * time);
void get12HTime(char* time);

#ifdef	__cplusplus
}
#endif


#endif	/* REALTIMECLOCK_H */

