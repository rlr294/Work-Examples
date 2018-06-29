/**
* @file Structures.c
*
* @brief Implementation file for Structures class
*
* @author Rex Rogers
*
* @details Implements all member methods of the Structures class
*
* @commit 12b42c2
* Rex Rogers (3 February 2017)
* Finished adding all error checking for the parser
*
* @commit fd579a2
* Rex Rogers (31 January 2017)
* Added documentation for all methods
*
* @commit 030ed4b
* Rex Rogers (30 January 2017)
* Changed makeNode to a static method, started mallocing for newNodes
*
* @commit 795a4a0
* Rex Rogers (27 January 2017)
* PrintConfig method developed, conversion methods added and developed.
*
* @commit 501b0d6
* Rex Rogers (26 January 2017)
* Initial development and testing of structures class
*
* @note Requires Structures.h
*/
#include "Structures.h"

static char* convertLogTo(enum logTo log);
static void makeNode(MetaDataNode *newNode, char newCommand,
        char newOperation[10], int newCycleTime);


// Free Function Implementation ///////////////////////////////////

/*
* @brief Converts the cpuSchedulingCode enum to the strings they represent
*
* @param[in] code
*            an enum handling the 3 values the config's 'CPU Scheduling Code'
*            can be
*
* @return the string that the number stored in code represents
*
* @note: None
*/
char* convertSchedulingCode(enum cpuSchedulingCode code)
{
    static char * strings[6] = {"FCFS-N", "FCFS-N", "SJF-N", "SRTF-P",
        "FCFS-P", "RR-P"};

    return strings[code];
}

/*
* @brief Converts the logTo enum to the strings they represent
*
* @param[in] log
*            an enum handling the 3 values the config's 'Log To' can be
*
* @return the string that the number stored in log represents
*
* @note: None
*/
static char* convertLogTo(enum logTo log)
{
    static char * strings[3] = {"Monitor", "File", "Both"};

    return strings[log];
}

/*
* @brief Inputs data into a meta data node
*
* @pre newNode This node should not have been used yet, it's current values
                should be NULL
*
* @param[in] newNode
*            points to the node for the data to be stored in
*
* @param[in] newCommand
*            Holds the command of the new meta data operation
*
* @param[in] newOperation[10]
*            Holds the operation of the new meta data operation
*
* @param[in] newCycleTime
*            Holds the cycle time of the new meta data operation
*
* @return None
*
* @note: None
*/
static void makeNode(MetaDataNode *newNode, char newCommand,
        char newOperation[10], int newCycleTime)
{
    newNode->command = newCommand;
    strcpy(newNode->operation, newOperation);
    newNode->cycleTime = newCycleTime;
    newNode->nextNode = NULL;
}

/*
* @brief Creates a new node and adds it to the end of the list
*
* @details The values passed to the function are stored within the new node
*
* @param[in] head
*            points to the head of the meta data linked list
*
* @param[in] newCommand
*            Holds the command of the new meta data operation
*
* @param[in] newoperation[10]
*            Holds the operation of the new meta data operation
*
* @param[in] newCycleTime
*            Holds the cycle time of the new meta data operation
*
* @return None
*
* @note: None
*/
void AddToList(MetaDataNode *head, char newCommand,
        char newoperation[10], int newCycleTime)
{
    MetaDataNode *currentNode = head;

    MetaDataNode *newNode = malloc(sizeof(MetaDataNode));
    makeNode(newNode, newCommand, newoperation, newCycleTime);

    while(currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
    }
    currentNode->nextNode = newNode;
}

/*
* @brief Prints the contents of the meta data file
*
* @details Takes in the head of a linked list storing the meta data information
*          and prints each nodes elements to the command line
*
* @pre MetaDataNode *head A pointer to the head of a linked list containing all
*      meta data information
*
* @post The command line will have all meta data printed to it
*
* @param[in] head
*            points to the head of the meta data linked list
*
* @return None
*
* @note: None
*/
void PrintList(MetaDataNode *head)
{
    MetaDataNode *currentNode = head;
    printf("========META DATA========\n\n");
    while(currentNode != NULL)
    {
        printf("Command: %c\n", currentNode->command);
        printf("Operation: %s\n", currentNode->operation);
        printf("Cycle Time: %i\n\n", currentNode->cycleTime);
        currentNode = currentNode->nextNode;
    }
}

/*
* @brief Prints the contents of the configuration file
*
* @details Takes in a data structure storing the configuration information
*          and prints each of its elements to the command line
*
* @pre ConfigInfo *configData A pointer to a structure containing all
*      configuration information
*
* @post The command line will have all configuration data printed to it
*
* @param[in] configData
*            holds configuration information
*
* @return None
*
* @note: None
*/
void PrintConfig(ConfigInfo *configData)
{
    printf("Start Simulator Configuration File\n");
    printf("Version/Phase: %d\n", configData->versionPhase);
    printf("File Path: %s\n", configData->filePath);
    printf("CPU Scheduling Code: %s\n",
        convertSchedulingCode(configData->cpuSchedulingCode));
    printf("Quantum Time (cycles): %d\n", configData->quantumTime);
    printf("Memory Available (KB): %d\n", configData->memoryAvailable);
    printf("Processor Cycle Time (msec): %d\n", configData->pCycleTime);
    printf("I/O Cycle Time (msec): %d\n", configData->ioCycleTime);
    printf("Log to: %s\n", convertLogTo(configData->logTo));
    printf("Log File Path: %s\n", configData->logFilePath);
    printf("End Simulator Configuration File.\n\n");
}

char* NodeToString(MetaDataNode *node)
{
    char* string = malloc(50);

    if(node->command == 'S')
    {
        snprintf(string, 50, "OS");
    }
    else if(node->command == 'A')
    {
        snprintf(string, 50, "PA");
    }
    else if(node->command == 'P')
    {
        snprintf(string, 50, "Run operation");
    }
    else if(node->command == 'M')
    {
        snprintf(string, 50, "Memory management %s action", node->operation);
    }
    else if(node->command == 'I')
    {
        snprintf(string, 50, "%s input", node->operation);
    }
    else if(node->command == 'O')
    {
        snprintf(string, 50, "%s output", node->operation);
    }
    else
    {
        snprintf(string, 50, "error");
    }

    return string;
}
