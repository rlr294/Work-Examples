/**
* @file Process.h
*
* @brief Header file for Processes
*
* @author Rex Rogers
*
* @details Contains methods for creating new processes
* and managing processes
*
* @commit 501b0d6
* Rex Rogers (17 February 2017)
* Basic creation of this file
*
* @note requires Structures.h, SimpleTimer.h, SimpleTimer.c
*/
#ifndef PROCESS_H
#define PROCESS_H

#include "Structures.h"
#include "SimpleTimer.h"
#include "Sim05.h"
#include <pthread.h>

#define PROC_READY 0
#define PROC_BLOCK 1
#define PROC_EXIT 2

void shortestJobFirstSort(ProcessListNode *start);
void CreateProcesses(ProcessListNode*, MetaDataNode*, ConfigInfo*);
int Run(PCB*, ConfigInfo*, char*, char*);
int PreemptiveRun(PCB**, ConfigInfo*, char*, char*, QueueNode**, QueueNode**);
    //The queue nodes had to become double pointers for problem 1
void SetReady(PCB*);
void SetRunning(PCB*);
void SetBlocked(PCB*);
void SetExit(PCB*);


#endif //STRUCTURES_H
