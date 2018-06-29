// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.c
 *
 * @brief Implementation file for using a timer with micro-second precision
 *
 * @author Michael Leverington
 *
 * @details Implements member methods for timing
 *
 * @version 2.10 (21 February 2017)
 *          2.00 (13 January 2017)
 *          1.00 (11 September 2015)
 *
 * @Note Requires SimpleTimer.h.
 *
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLETIMER_CPP
#define SIMPLETIMER_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleTimer.h"

//changed from Leverington's verison by making timeStr keep a running total
//and by making GET_TIME_DIFF usable while the timer is running
void accessTimer(int controlCode, char *timeStr)
{
    static Boolean running = FALSE;
    static Boolean dataGood = FALSE;
    static int startSec = 0, endSec = 0, startUSec = 0, endUSec = 0;
    struct timeval startData, endData;
    //double fpTime = 0.0;
    int secDiff, usecDiff;

    switch(controlCode)
    {
        case START_TIMER:
           gettimeofday( &startData, NULL );
           running = TRUE;
           dataGood = FALSE;

           startSec = startData.tv_sec;
           startUSec = startData.tv_usec;
           //fpTime = (double) startSec + (double) startUSec / 1000000;
           break;

        case STOP_TIMER:
           if(running == TRUE)
           {
               gettimeofday( &endData, NULL );
               running = FALSE;
               dataGood = TRUE;
               endSec = endData.tv_sec;
               endUSec = endData.tv_usec;
               //fpTime = (double) endSec + (double) endUSec / 1000000;
           }

           // assume timer not running
           else
           {
               dataGood = FALSE;
               //fpTime = 0.0;
           }

           break;

        case RESET_TIMER:
            running = FALSE;
            dataGood = FALSE;
            startSec = 0;
            endSec = 0;
            startUSec = 0;
            endUSec = 0;
            //fpTime = 0.0;
            break;

        case GET_TIME_DIFF:
            //stop the timer
            if(running == TRUE)
            {
                gettimeofday(&endData, NULL);
                running = FALSE;
                dataGood = TRUE;
                endSec = endData.tv_sec;
                endUSec = endData.tv_usec;
                //fpTime = (double) endSec + (double) endUSec / 1000000;
            }

            // assume timer not running
            else
            {
                dataGood = FALSE;
                //fpTime = 0.0;
            }

            //get the time since the timer was started
            if(running == FALSE && dataGood == TRUE)
            {
                secDiff = endSec - startSec;
                usecDiff = endUSec - startUSec;
                //fpTime = (double) secDiff + (double) usecDiff / 1000000;

                if(usecDiff < 0)
                {
                    usecDiff = usecDiff + 1000000;
                    secDiff = secDiff - 1;
                }

                timeToString(secDiff, usecDiff, timeStr);

                //Start Timer
                gettimeofday(&startData, NULL);
                running = TRUE;
                dataGood = FALSE;

                //fpTime = (double) startSec + (double) startUSec / 1000000;
            }

           // assume timer running or data not good
           else
           {
               //fpTime = 0.0;
           }

           break;
    }

    //return fpTime;
}

/* This is a bit of a drawn-out function, but it is written
   to force the time result to always be in the form x.xxxxxxx
   when printed as a string; this will not always be the case
   when the time is presented as a floating point number
*/
void timeToString( int secTime, int uSecTime, char *timeStr )
{
    int low, high, index = 0;
    char temp;

    while(uSecTime > 0)
    {
        timeStr[index] = (char) (uSecTime % 10 + '0');
        uSecTime /= 10;

        index++;
    }

    while(index < 6)
    {
        timeStr[index] = '0';

        index++;
    }

    timeStr[index] = RADIX_POINT;

    index++;

    if(secTime == 0)
    {
        timeStr[index] = '0';

        index++;
       }

    while(secTime > 0)
    {
        timeStr[index] = (char) (secTime % 10 + '0');

        secTime /= 10;

        index++;
    }

    timeStr[index] = NULL_CHAR;

    low = 0; high = index - 1;

    while(low < high)
    {
        temp = timeStr[low];
        timeStr[low] = timeStr[high];
        timeStr[high] = temp;

        low++; high--;
    }
}

/*
* @brief Waits for a given amount of milliseconds
*
* @param[in] milliseconds
*            stores how many milliseconds to wait for
*
* @return None
*
* @note: None
*/
void delay(int milliseconds)
{
    long waitTime;
    clock_t currentTime, startTime;
    waitTime = milliseconds * (CLOCKS_PER_SEC / 1000);
    currentTime = startTime = clock();
    while((currentTime-startTime) < waitTime )
        currentTime = clock();
}

#endif // ifndef SIMPLETIMER_CPP
