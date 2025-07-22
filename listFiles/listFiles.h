//****************************** ListFiles *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// Summary : Contains all global constants and forward declarations required for
//           listFiles.c file functions.
// Note    : None.
//******************************************************************************
#ifndef _LIST_FILES_H
#define _LIST_FILES_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "../common.h"

//******************************* Global Types *********************************
typedef struct FILE_DETAILS
{
    uint8 *ucFileName;
    uint8 *ucFileType;
    uint32 ulFileSize;
    struct FILE_DETAILS *pstNext;
} FILE_DETAILS;

//***************************** Global Constants *******************************
#define FILE_TYPE (8)
#define FILE_SEPARATOR ("/")

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool listFilesCheckDirectory(char *pcDirectoryPath);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _LIST_FILES_H
       // EOF