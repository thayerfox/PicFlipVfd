/* 
 * File:   config.h
 * Author: jon
 *
 * Created on May 28, 2013, 8:05 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>



#ifdef	__cplusplus
extern "C" {
#endif

#define TO_K(x) (x * 1000)
#define TO_M(x) (TO_K(x) * 1000)

#define _XTAL_FREQ 8000000
#define FOSC _XTAL_FREQ
#define FCY (FOSC/2)

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

