// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.h
 *
 * @brief Header file for micro-second precision timer
 *
 * @author Michael Leverington
 *
 * @details Specifies all member methods of the SimpleTimer
 *
 * @version 2.10 (21 February 2017)
 *          2.00 (13 January 2017)
 *          1.00 (11 September 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

// Header files ///////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sim05.h"

// Global Constants  //////////////////////////////////////////////////////////

enum TIMER_CTRL_CODES { START_TIMER, STOP_TIMER, RESET_TIMER, GET_TIME_DIFF };

#define RADIX_POINT '.'
#define NULL_CHAR '\0'


// Function Prototyp  /////////////////////////////////////////////////////////

void accessTimer( int controlCode, char *timeStr );
void timeToString( int secTime, int uSecTime, char *timeStr );
void delay(int milliseconds);

#endif // SIMPLETIMER_H
