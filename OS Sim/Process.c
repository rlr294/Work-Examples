/**
* @file Process.c
*
* @brief Implementation file for Process class
*
* @author Rex Rogers
*
* @details Implements all member methods of the Process class
*
* @commit
* Rex Rogers (23 February 2017)
* Added support for multiple processes
*
* @commit
* Rex Rogers (21 February 2017)
* Implements the methods
*
* @commit
* Rex Rogers (14 February 2017)
* Basic creation of this file
*
* @note Requires Process.h
*/

#include "Process.h"

// Free Function Implementation ///////////////////////////////////

/*
* @brief Calculates the total cycle time of a process in ms
*
* @param[in] node
*            points to the head node for the process
*
* @param[in] configData
*            points to the structure holding the configuration info
*
* @return Cycle time of process in Miliseconds
*
* @note: None
*/
int calcCycleTime(MetaDataNode *node, ConfigInfo *configData)
{
    //cycle times for I/O commands
    if(node->command == 'I'
        || node->command == 'O')
    {
        return configData->ioCycleTime * node->cycleTime;
    }
    //cycle times for memory commands
    else if(node->command == 'M')
    {
        return 0;
    }
    //cycle times for all other commands
    else
    {
        return configData->pCycleTime * node->cycleTime;
    }
}

/*
* @brief Creates all processses outlined in the meta-data file and
*        stores them in the ProcessList passed as a parameter
*
* @param[in] list
*            points to the list of PCB's
*
* @param[in] node
*            points to the head node for the process
*
* @param[in] configData
*            points to the data from the config file
*
* @return None
*
* @note: None
*/
void CreateProcesses(ProcessListNode *list, MetaDataNode *node,
                      ConfigInfo *configData)
{
    PCB *newProc;
    ProcessListNode *newListNode;
    MetaDataNode *tempNode;
    MetaDataNode *tempNode2;
    int procNum = 0;

    while(node->nextNode != NULL)
    {
        tempNode = node->nextNode;

        //handles the start of a new process
        if(node->command == 'A' && strcmp(node->operation, "start") == 0)
        {
            newProc = malloc(sizeof(PCB));
            newProc->state = New;
            newProc->currentNode = node;
            newProc->procNum = procNum;
            newProc->cycleTime = 0;
            procNum++;

            //handle adding the first process
            if(list->process == NULL)
            {
                list->process = newProc;
            }
            else
            {
                newListNode = malloc(sizeof(ProcessListNode));
                list->nextProcess = newListNode;
                list = list->nextProcess;
                list->process = newProc;
                list->nextProcess = NULL;
            }
        }
        //handles the end of a process
        else if(node->command == 'A' && strcmp(node->operation, "end") == 0)
        {
            node->nextNode = NULL;

            tempNode2 = newProc->currentNode;
            while(tempNode2 != NULL)
            {
                newProc->cycleTime = newProc->cycleTime
                    + calcCycleTime(tempNode2, configData);

                tempNode2 = tempNode2->nextNode;
            }
        }
        node = tempNode;
    }
}

/*
* @brief function for pthreads to run that handles the cycle time for
*        I/O operations
*
* @param[in] ptr
*            pointer to the data being passed
*
* @return None
*
* @note: None
*/
void NonPreemptiveIO(void *ptr)
{
    IOdata *data;
    data = (IOdata *) ptr;
    delay(data->delay);

    pthread_exit(0);
}

void PreemptiveIO(void *ptr)
{
    IOdata *data;
    data = (IOdata *) ptr;
    delay(data->delay);
    accessTimer(GET_TIME_DIFF, data->timer);
    printf("Time: %9s, Process %d, %s end\n", data->timer,
         data->process->procNum, NodeToString(data->process->currentNode));

    data->process->state = Ready;

    if(data->configData->cpuSchedulingCode == SRTFP)
    {
        *data->interuptQueue = EnqueueSRTF(data->interuptQueue, data->process);
    }
    else if(data->configData->cpuSchedulingCode == RRP)
    {
        *data->interuptQueue = EnqueueRR(data->interuptQueue, data->process);
    }
    else
    {
        *data->interuptQueue = EnqueueFCFS(data->interuptQueue, data->process);
    }
}

/*
* @brief Runs the current command that a processes is looking at
*
* @param[in] process
*            points to the PCB of a process
*
* @param[in] configData
*            points to the data from the config file
*
* @param[in] timer
*            the current timer value
*
* @param[in] filePrint
*            the buffer where all things to be logged to file is stored
*
* @return 0 if no errors, negative for errors
*
* @note: None
*/
int Run(PCB *process, ConfigInfo *configData, char* timer, char* filePrint)
{
    char* monitorPrint = malloc(100 * sizeof(char));
    pthread_t thread1;
    IOdata data1;

    if(process->currentNode->cycleTime != 0)
    {
        //prints the start time
        accessTimer(GET_TIME_DIFF, timer);
        snprintf(monitorPrint, 100,
            "Time: %9s, Process %d, %s start\n",
            timer, process->procNum, NodeToString(process->currentNode));
        HandlePrint(monitorPrint, filePrint, configData);

        //For I/O operations use a POSIX thread to manage cycle times
        if(process->currentNode->command == 'I'
            || process->currentNode->command == 'O')
        {
            data1.delay = calcCycleTime(process->currentNode, configData);
            pthread_create(&thread1, NULL,
                    (void *) &NonPreemptiveIO, (void *) &data1);

            pthread_join(thread1, NULL);
        }
        else
        {
            delay(calcCycleTime(process->currentNode, configData));
        }

        //prints the end time
        accessTimer(GET_TIME_DIFF, timer);
        snprintf(monitorPrint, 100,
            "Time: %9s, Process %d, %s end\n",
            timer, process->procNum, NodeToString(process->currentNode));
        HandlePrint(monitorPrint, filePrint, configData);

    }

    process->currentNode = process->currentNode->nextNode;

    return 0;
}

int PreemptiveRun(PCB **process, ConfigInfo *configData, char* timer,
    char* filePrint, QueueNode** interuptQueue, QueueNode** processQueue)
{
    char* monitorPrint = malloc(100 * sizeof(char));
    pthread_t thread1;
    IOdata *data1 = malloc(sizeof(IOdata));

    //handle starts
    if((*process)->currentNode->cycleTime == 0 &&
        (*process)->currentNode->nextNode != NULL)
    {
        (*process)->currentNode = (*process)->currentNode->nextNode;
    }
    if((*process)->currentNode->cycleTime != 0)
    {
        //prints the start time
        accessTimer(GET_TIME_DIFF, timer);
        snprintf(monitorPrint, 100,
            "Time: %9s, Process %d, %s start\n",
            timer, (*process)->procNum, NodeToString((*process)->currentNode));
        HandlePrint(monitorPrint, filePrint, configData);


        //For I/O operations use a POSIX thread to manage cycle times
        if((*process)->currentNode->command == 'I'
            || (*process)->currentNode->command == 'O')
        {
            data1->delay = calcCycleTime((*process)->currentNode, configData);
            data1->timer = timer;
            data1->configData = configData;
            data1->process = (*process);
            data1->interuptQueue = interuptQueue;
            pthread_create(&thread1, NULL,
                    (void *) &PreemptiveIO, (void *) data1);

            //Essential step for issue 2, implementing SRTF-P
            (*process)->cycleTime = (*process)->cycleTime -
                calcCycleTime((*process)->currentNode, configData);

            (*process)->currentNode = (*process)->currentNode->nextNode;
            return PROC_BLOCK;
        }
        //no delay on memory
        else if ((*process)->currentNode->command == 'M') {
            accessTimer(GET_TIME_DIFF, timer);
            snprintf(monitorPrint, 100,
                "Time: %9s, Process %d, %s end\n",
                timer, (*process)->procNum, NodeToString((*process)->currentNode));
            HandlePrint(monitorPrint, filePrint, configData);

        }
        else
        {
            if(configData->cpuSchedulingCode == RRP)
            {
                if((*process)->currentNode->cycleTime * configData->pCycleTime
                    > configData->quantumTime)
                {
                    delay(configData->quantumTime);
                    (*process)->currentNode->cycleTime -= configData->quantumTime;
                }
                else
                {
                    delay((*process)->currentNode->cycleTime);
                    (*process)->currentNode->cycleTime = 0;
                }
            }
            else
            {
                while(interuptQueue == NULL &&
                    (*process)->currentNode->cycleTime > 0)
                {
                    delay(configData->pCycleTime);
                    (*process)->currentNode->cycleTime =
                            (*process)->currentNode->cycleTime - 1;
                }
            }

            if((*process)->currentNode->cycleTime == 0)
            {
                //prints the end time
                accessTimer(GET_TIME_DIFF, timer);
                snprintf(monitorPrint, 100,
                    "Time: %9s, Process %d, %s end\n", timer,
                    (*process)->procNum, NodeToString((*process)->currentNode));
                HandlePrint(monitorPrint, filePrint, configData);

            }
        }
    }
    if((*process)->currentNode->nextNode == NULL)
    {
        return PROC_EXIT;
    }
    else
    {
        //Reduces the cycle times as parts of the process are run
        (*process)->cycleTime = (*process)->cycleTime -
            calcCycleTime((*process)->currentNode, configData);

        (*process)->currentNode = (*process)->currentNode->nextNode;

        //handles the scheduling by doing the proper enqueue
        if(configData->cpuSchedulingCode == SRTFP)
        {
            *processQueue = EnqueueSRTF(processQueue, (*process));
        }
        else if(configData->cpuSchedulingCode == RRP)
        {
            *processQueue = EnqueueRR(processQueue, (*process));
        }
        else
        {
            *processQueue = EnqueueFCFS(processQueue, (*process));
        }

        return PROC_READY;
    }
}

/*
* @brief Sets a process to the ready state
*
* @param[in] process
*            points to the PCB of a process
*
* @return None
*
* @note: None
*/
void SetReady(PCB *process)
{
    process->state = Ready;
}

/*
* @brief Sets a process to the running state
*
* @param[in] process
*            points to the PCB of a process
*
* @return None
*
* @note: None
*/
void SetRunning(PCB *process)
{
    process->state = Running;
}

/*
* @brief Sets a process to the blocked state
*
* @param[in] process
*            points to the PCB of a process
*
* @return None
*
* @note: None
*/
void SetBlocked(PCB *process)
{
    process->state = Blocked;
}

/*
* @brief Sets a process to the exit state
*
* @param[in] process
*            points to the PCB of a process
*
* @return None
*
* @note: None
*/
void SetExit(PCB *process)
{
    process->state = Exit;
}
