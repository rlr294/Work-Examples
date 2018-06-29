/**
* @file Parser.h
*
* @brief Header file for the data parser
*
* @author Rex Rogers
*
* @details Contains methods for reading configuration and
* meta data files and storing them into structures
*
* @commit 12b42c2
* Rex Rogers (3 February 2017)
* Finished adding all error checking for the parser
*
* @commit 795a4a0
* Rex Rogers (27 January 2017)
* Added declarations for ReadConfig and ReadMetaData
*
* @commit 501b0d6
* Rex Rogers (26 January 2017)
* Basic creation of this file
*
* @note requires Sim05.h and Structures.h
*/
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Structures.h"
#include "Sim05.h"

#define NONE 0
#define FCFS_N 1
#define SJF_N 2
#define SRTF_P 3
#define FCFS_P 4
#define RR_P 5

#define LOG_TO_MONITOR 0
#define LOG_TO_FILE 1
#define LOG_TO_BOTH 2

#define CPU_SCHEDULING_CODE_ERROR -1
#define LOG_TO_ERROR -2
#define CONFIG_FILE_ERROR -3
#define META_DATA_FILE_ERROR -4
#define META_DATA_FORMAT_ERROR -5
#define CONFIG_FORMAT_ERROR -6
#define CONFIG_BOUNDS_ERROR -7
#define WRONG_VERSION -8

int ReadConfig(char* configFileName, ConfigInfo *configData);

int ReadMetaData(char* metaDataFileName, MetaDataNode *head);

#endif //PARSER_H
