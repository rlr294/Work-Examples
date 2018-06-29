/**
* @file structures.h
*
* @brief Header file for OS simulation structures
*
* @author Rex Rogers
*
* @details contains the data structures for containing the
* config data and meta data
*
* @commit 795a4a0
* C.S. Student (27 January 2017)
* Changed some of the method arguements to agree with Structures.c
*
* @commit 501b0d6
* Rex Rogers (26 January 2017)
* Structs developed and functions declared
*
* @note None
*/
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEQUEUE_SUCCESS 0
#define QUEUE_EMPTY 1

typedef struct
{
    int versionPhase;
    char filePath[40];
    enum cpuSchedulingCode {NONE, FCFSN, SJFN, SRTFP, FCFSP, RRP}
        cpuSchedulingCode;
    int quantumTime;
    int memoryAvailable;
    int pCycleTime;
    int ioCycleTime;
    enum logTo {Monitor, File, Both} logTo;
    char logFilePath[40];
} ConfigInfo;

typedef struct MetaDataNode
{
    char command;
    char operation[10];
    int cycleTime;
    struct MetaDataNode *nextNode;
} MetaDataNode;

typedef struct
{
    enum state {New, Ready, Running, Blocked, Exit} state;
    MetaDataNode *currentNode;
    int procNum;
    int cycleTime;
} PCB;

typedef struct ProcessListNode
{
    PCB *process;
    struct ProcessListNode *nextProcess;
} ProcessListNode;

typedef struct QueueNode {
	PCB *process;
	struct QueueNode* next;
} QueueNode;

typedef struct IOdata
{
    int delay;
    char* timer;
    PCB *process;
    QueueNode **interuptQueue;
    ConfigInfo *configData;
} IOdata;

typedef enum {FALSE, TRUE} Boolean;

char* convertSchedulingCode(enum cpuSchedulingCode code);

void AddToList(MetaDataNode *head, char newCommand, char newOpperation[10],
        int newCycleTime);

void PrintList(MetaDataNode *head);

void PrintConfig(ConfigInfo *configData);

char* NodeToString(MetaDataNode *node);

#endif //STRUCTURES_H
