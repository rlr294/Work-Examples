/**
* @file Parser.c
*
* @brief Implementation file for Parser class
*
* @details Implements all member methods of the Parser class
*
* @author Rex Rogers
*
* @commit 12b42c2
* Rex Rogers (3 February 2017)
* Finished adding all error checking for the parser
*
* @commit fd579a2
* Rex Rogers (31 January 2017)
* Added documentation for all methods, added error codes for file checks
*
* @commit 44c0cab
* Rex Rogers (31 January 2017)
* Added a null terminating character after parsing in operation
*
* @commit 030ed4b
* Rex Rogers (30 January 2017)
* Development of ReadMetaData
*
* @commit 795a4a0
* Rex Rogers (27 January 2017)
* Initial development of convertSchedulingCode,  convertLogTo, and ReadConfig
*
* @commit 501b0d6
* Rex Rogers (26 January 2017)
* Basic creation of this file
*
* @note Requires Parser.h
*/
#include "Parser.h"

static int ConvertSchedulingCode(char* codeString);
static int ConvertLogTo(char* logString);
static void RemoveSpaces(char* sourceString);
static Boolean IsValidCommand(char command);
static Boolean IsValidOperation(char* operation);
static int HandleInstruction(char* instruction, MetaDataNode *head);
static int CheckConfigData(ConfigInfo *configData);

// Free Function Implementation ///////////////////////////////////

/*
* @brief Converts the 'CPU scheduling code' string to an enum representing it
*
* @param[in] codeString
*            holds the string for the 'CPU scheduling code'
*
* @return A number used for an enum to represent the config file's
*        'CPU scheduling code', negative nubers represent error codes
*
* @note: None
*/
static int ConvertSchedulingCode(char* codeString)
{
    if(strcmp(codeString, "NONE") == 0)
    {
        return FCFS_N;
    }
    else if(strcmp(codeString, "FCFS-N") == 0)
    {
        return FCFS_N;
    }
    else if(strcmp(codeString, "SJF-N") == 0)
    {
        return SJF_N;
    }
    else if(strcmp(codeString, "SRTF-P") == 0 )
    {
        return SRTF_P;
    }
    else if(strcmp(codeString, "FCFS-P") == 0)
    {
        return FCFS_P;
    }
    else if(strcmp(codeString, "RR-P") == 0)
    {
        return RR_P;
    }
    else
    {
        return CPU_SCHEDULING_CODE_ERROR;
    }
}

/*
* @brief Converts the 'Log To' string to an enum representing it
*
* @param[in] codeString
*            holds the string for the 'Log To'
*
* @return A number used for an enum to represent the config file's
*        'Log To', negative nubers represent error codes
*
* @note: None
*/
static int ConvertLogTo(char* logString)
{
    if(strcmp(logString, "Monitor") == 0)
    {
        return LOG_TO_MONITOR;
    }
    else if(strcmp(logString, "File") == 0)
    {
        return LOG_TO_FILE;
    }
    else if(strcmp(logString, "Both") == 0)
    {
        return LOG_TO_BOTH;
    }
    else
    {
        return LOG_TO_ERROR;
    }
}

/*
* @brief Takes a string and removes all spaces and new lines from it
*
* @pre char* sourceString is a pointer to a string
*
* @param[in] sourceString
*            points to the string to be changed
*
* @return None
*
* @note: None
*/
static void RemoveSpaces(char* sourceString)
{
  char* tempString1 = sourceString;
  char* tempString2 = sourceString;
  while(*tempString2 != 0)
  {
    *tempString1 = *tempString2++;
    if(*tempString1 != ' ' && *tempString1 != '\n')
    {
        tempString1++;
    }
  }
  *tempString1 = 0;
}

/*
* @brief Checks a command to ensure it is one of the valid values
*
* @param[in] operation
*            holds the command
*
* @return True if valid, else false
*
* @note: None
*/
static Boolean IsValidCommand(char command)
{
    if(command == 'S' || command == 'A' || command == 'P'
        || command == 'M' || command == 'I' || command == 'O')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/*
* @brief Checks an operation to ensure it is one of the valid values
*
* @param[in] operation
*            string holding the operation
*
* @return True if valid, else false
*
* @note: None
*/
static Boolean IsValidOperation(char* operation)
{
    if(strcmp(operation, "access") == 0|| strcmp(operation, "allocate") == 0
        || strcmp(operation, "end") == 0 || strcmp(operation, "harddrive") == 0
        || strcmp(operation, "keyboard") == 0
        || strcmp(operation, "printer") == 0||strcmp(operation, "monitor") == 0
        || strcmp(operation, "run") == 0 || strcmp(operation, "start") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
* @brief Subroutine of Read Meta data that takes an instruction and stores it
*        in a node
*
* @details If this is the first instruction being read the data is stored in
*          head, otherwise it is stored in a new node that is put at the
*          end of the linked list that head points to
*
* @param[in] instruction
*            holds the string containing the meta data instruction
*
* @param[in] head
*            pointer to the head of the linked list where the meta data
*            will be stored
*
* @return error codes: 0 represents no error, negative numbers represent errors
*
* @note: None
*/
static int HandleInstruction(char* instruction, MetaDataNode *head)
{
    char* openParenthesis;
    char* closeParenthesis;
    int range;
    char command;
    char* operation;
    char* stringToLongPtr;
    int cycleTime;

    command = instruction[0];
    if(!IsValidCommand(command) || instruction[1] != '(')
    {
        return META_DATA_FORMAT_ERROR;
    }

    //gets the location of the parenthesis and how many characters are
    //between them
    openParenthesis = strchr(instruction, '(');
    closeParenthesis = strchr(instruction, ')');
    if(openParenthesis == NULL || closeParenthesis == NULL)
    {
        return META_DATA_FORMAT_ERROR;
    }
    range = closeParenthesis - openParenthesis - 1;

    //stores the string between the parenthesis into operation
    operation = malloc(sizeof(range));
    strncpy(operation, openParenthesis + 1, range);
    operation[range] = '\0';
    if(!IsValidOperation(operation))
    {
        return META_DATA_FORMAT_ERROR;
    }
    if(strcmp(operation, "harddrive") == 0)
    {
        strcpy(operation, "hard drive");
    }

    //stores the number after the close parenthesis into cycleTime
    //stringToLongPtr catches the cases when the file formatting is wrong
    cycleTime = strtol(closeParenthesis + 1, &stringToLongPtr, 10);
    if(stringToLongPtr == closeParenthesis + 1 || stringToLongPtr[0] != '\0')
    {
        return META_DATA_FORMAT_ERROR;
    }

    //if head hasn't been used yet store the data in head,
    //otherwise use AddToList to create a new node to hold the data
    if(!head->command)
    {
        head->command = command;
        strcpy(head->operation, operation);
        head->cycleTime = cycleTime;
    }
    else
    {
        AddToList(head, command, operation, cycleTime);
    }

    free(operation);
    return 0;
}

/*
* @brief Checks a ConfigInfo struct to ensure that all it's elements have
*        been assigned
*
* @param[in] configData
*            pointer to the struct where the configuration data is be stored
*
* @return error codes: 0 represents no error, negative numbers represent errors
*
* @note: None
*/
static int CheckConfigData(ConfigInfo *configData)
{
    if(configData->versionPhase != 5)
    {
        return WRONG_VERSION;
    }

    if(configData->quantumTime < 0 || configData->quantumTime > 100)
    {
        return CONFIG_BOUNDS_ERROR;
    }

    if(configData->memoryAvailable < 0
        || configData->memoryAvailable > 1048576)
    {
        return CONFIG_BOUNDS_ERROR;
    }

    if(configData->pCycleTime < 1
        || configData->pCycleTime > 1000)
    {
        return CONFIG_BOUNDS_ERROR;
    }

    if(configData->ioCycleTime < 1 || configData->ioCycleTime > 10000)
    {
        return CONFIG_BOUNDS_ERROR;
    }

    if(configData->versionPhase < 0 || configData->filePath[0] == '\0'
        || configData->quantumTime < 0
        || configData->memoryAvailable < 0
        || configData->pCycleTime < 0
        || configData->ioCycleTime < 0
        || configData->logFilePath[0] == '\0')
    {
        return CONFIG_FORMAT_ERROR;
    }
    else
    {
        return 0;
    }
}

/*
* @brief Reads configuration information from a config file and stores it
*        in a ConfigInfo struct
*
* @param[in] configFileName
*            holds the string for the configuration file name
*
* @param[in] configData
*            pointer to the struct where the configuration data will be stored
*
* @return error codes: 0 represents no error, negative numbers represent errors
*
* @note: None
*/
int ReadConfig(char* configFileName, ConfigInfo *configData)
{
    char *schedulingCode = malloc(7 * sizeof(char));
    char *logTo = malloc(7 * sizeof(char));
    FILE *configFile;
    char line[256];
    int errorNum = 0;

    configFile = fopen(configFileName, "r");

    if(configFile == NULL)
    {
        return CONFIG_FILE_ERROR;
    }

    //reads information in each line into configData
    while(fgets(line, sizeof(line), configFile))
    {
        RemoveSpaces(line);
        sscanf(line, "Version/Phase:%d", &configData->versionPhase);
        sscanf(line, "FilePath:%s", configData->filePath);
        sscanf(line, "CPUSchedulingCode:%s", schedulingCode);
        sscanf(line, "QuantumTime(cycles):%d",
            &configData->quantumTime);

        sscanf(line, "MemoryAvailable(KB):%d",
            &configData->memoryAvailable);

        sscanf(line, "ProcessorCycleTime(msec):%d",
            &configData->pCycleTime);

        sscanf(line, "I/OCycleTime(msec):%d",
            &configData->ioCycleTime);

        sscanf(line, "LogTo:%s", logTo);
        sscanf(line, "LogFilePath:%s", configData->logFilePath);
    }
    //Checks to ensure all config data was formatted correctly and within bounds
    configData->cpuSchedulingCode = ConvertSchedulingCode(schedulingCode);
    if(configData->cpuSchedulingCode == CPU_SCHEDULING_CODE_ERROR)
    {
        return CPU_SCHEDULING_CODE_ERROR;
    }

    configData->logTo = ConvertLogTo(logTo);
    if(configData->logTo == LOG_TO_ERROR)
    {
        return LOG_TO_ERROR;
    }

    errorNum = CheckConfigData(configData);
    if(errorNum < 0)
    {
        return errorNum;
    }


    fclose(configFile);
    return 0;
}

/*
* @brief Reads meta data information from a meta data file and stores it
*        in a linked list
*
* @param[in] metaDataFileName
*            holds the string for the meta data name
*
* @param[in] head
*            pointer to the head of the linked list where the meta data
*            will be stored
*
* @return error codes: 0 represents no error, negative numbers represent errors
*
* @note: None
*/
int ReadMetaData(char* metaDataFileName, MetaDataNode *head)
{
    char line[256];
    char* instruction;
    FILE *metaDataFile;
    int errorNum = 0;

    metaDataFile = fopen(metaDataFileName, "r");

    if(metaDataFile == NULL)
    {
        return META_DATA_FILE_ERROR;
    }

    //Reads through the metaDataFile line by line and stores the
    //information in a linked list
    while(fgets(line, sizeof(line), metaDataFile))
    {
        RemoveSpaces(line);
        if(strcmp(line, "EndProgramMeta-DataCode.") != 0
            && strcmp(line, "StartProgramMeta-DataCode:") != 0)
        {
            instruction = strtok(line, ";");
            while(instruction != NULL && instruction[0] != '\n')
            {
                errorNum = HandleInstruction(instruction, head);
                if(errorNum < 0)
                {
                    return errorNum;
                }

                instruction = strtok(NULL, ";.");
            }
        }
    }

    fclose(metaDataFile);

    return 0;
}
