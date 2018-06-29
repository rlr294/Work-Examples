/**
* @file Sim05.h
*
* @brief Header file for the simulation program
*
* @author Rex Rogers
*
* @details Executes all the commands needed to make the program run
*
* @commit 501b0d6
* Rex Rogers (26 January 2017)
* Definition of Boolean
*
* @note None
*/
#ifndef SIM05_H
#define SIM05_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "Process.h"
#include "SimpleTimer.h"
#include "Structures.h"

void HandlePrint(char*, char*, ConfigInfo*);

QueueNode* EnqueueFCFS(QueueNode **head, PCB *process);

QueueNode* EnqueueSRTF(QueueNode **head, PCB *process);

QueueNode* EnqueueRR(QueueNode **head, PCB *process);

PCB* Dequeue(QueueNode **head);

#endif //SIM05_H
