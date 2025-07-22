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
// Inputs  : pstDirectory - Pointer to the directory.
//           pcPath - Path to directory or directory name.
//           pstContents - Pointer to the contents of directory.
// Outputs : pstContents - Pointer to contents of directory getting modified.
// Return  : blFunctionStatus - True if directory opened successfully,
//           else false.
// Notes   : None.
//******************************************************************************
bool directoryOperationOpen(DIR **pstDirectory, char **pcPath,
                            struct dirent **pstContents)
{
    bool blFunctionStatus = false;

    if ((NULL != pstDirectory) && (NULL != *pcPath) && (NULL != pstContents))
    {
        *pstDirectory = opendir(*pcPath);

        if (NULL != *pstDirectory)
        {
            blFunctionStatus = true;
        }
        else
        {
            printf("Directory cannot be opened\n");
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
bool directoryOperationClose(DIR **pstDirectory)
{
    bool blFunctionStatus = false;

    if (NULL != *pstDirectory)
    {
        if (0 == closedir(*pstDirectory))
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