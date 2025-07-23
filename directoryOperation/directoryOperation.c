//****************************** directoryOperation ****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : directoryOperation.c
// Summary : Contains functions that perform the directory operations.
// Note    : Header file included.
// Author  : Meenakshy G
// Date    : 18/JULY/2025
//******************************************************************************
//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <dirent.h>
#include "../common.h"
#include "fileOperation.h"
#include "listFiles.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//****************************.directoryOperationOpen.**************************
// Purpose : Open the given directory.
// Inputs  : ppcPath - directory path pointer.
// Outputs : ppstDirectory - directory pointer.
// Return  : True if directory opened successfully, else false.
// Notes   : None.
//******************************************************************************
bool directoryOperationOpen(DIR **ppstDirectory, char **ppcPath)
{
    bool blFunctionStatus = false;

    if ((NULL != ppstDirectory) && (NULL != *ppcPath))
    {
        *ppstDirectory = opendir(*ppcPath);

        if (NULL != *ppstDirectory)
        {
            blFunctionStatus = true;
        }
        else
        {
            printf("Directory cannot be opened: Not a directory \n");
        }
    }

    return blFunctionStatus;
}

//*************************.directoryOperationClose.****************************
// Purpose : Close the given directory.
// Inputs  : ppstDirectory - directory pointer.
// Outputs : None.
// Return  : True if directory closed successfully, else false.
// Notes   : None.
//******************************************************************************
bool directoryOperationClose(DIR **ppstDirectory)
{
    bool blFunctionStatus = false;

    if (NULL != *ppstDirectory)
    {
        if (0 == closedir(*ppstDirectory))
        {
            blFunctionStatus = true;
        }
        else
        {
            printf("Cannot close directory");
        }
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF