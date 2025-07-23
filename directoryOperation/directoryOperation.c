//****************************** directoryOperation ****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : directoryOperation.c
// Summary : All the directory operation functions are defined.
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
// Purpose : To open the input directory.
// Inputs  : ppcPath - Path to directory or directory name.
// Outputs : ppstDirectory - Pointer to the directory.
// Return  : blFunctionStatus - True if directory opened successfully,
//           else false.
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
// Purpose : To close the input directory.
// Inputs  : pstDirectory - Pointer to the directory.
// Outputs : None.
// Return  : blFunctionStatus - True if directory closed successfully,
//           else false.
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