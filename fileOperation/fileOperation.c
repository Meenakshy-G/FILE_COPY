//**************************** FileOperations **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : fileOperation.c
// Summary : Contains the functions which does the operations on file.
// Note    : Header file included.
// Author  : Meenakshy G
// Date    : 11/JULY/2025
//******************************************************************************
//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "../common.h"
#include "fileOperation.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//****************************.fileOperationOpen.*******************************
// Purpose : Open the file in read or write mode.
// Inputs  : pcFileName - file name pointer.
//           pstMode - open mode pointer.
// Outputs : ppstFile - file pointer.
// Return  : True if file opened succesfully, else false.
// Notes   : None.
//******************************************************************************
bool fileOperationOpen(FILE **pstFile, char *pcFileName, char *pstMode)
{
    bool blFunctionStatus = false;

    if ((NULL != pstFile) && (NULL != pcFileName) && (NULL != pstMode))
    {
        if (NULL != (*pstFile = fopen(pcFileName, pstMode)))
        {
            blFunctionStatus = true;
        }
        else
        {
            printf("Error opening file\n");
        }
    }
    else
    {
        printf("Input pointer is NULL\n");
    }

    return blFunctionStatus;
}

//*************************.fileOperationClose.*********************************
// Purpose : Close the given file.
// Inputs  : pstFile - file pointer.
// Outputs : None.
// Return  : True if file closed successfully, else false.
// Notes   : None.
//******************************************************************************
bool fileOperationClose(FILE *pstFile)
{
    bool blFunctionStatus = false;

    if (pstFile != NULL)
    {
        if (0 == fclose(pstFile))
        {
            blFunctionStatus = true;
        }
        else
        {
            perror("Error closing the file");
        }
    }
    else
    {
        printf("File pointer is NULL");
    }

    return blFunctionStatus;
}

//***************************.fileOperationSize.********************************
// Purpose : Determine size of the given file.
// Inputs  : pstFile - file pointer.
// Outputs : pulFileSize - size pointer.
// Return  : True if size is determined successfully, else false.
// Notes   : None.
//******************************************************************************
bool fileOperationSize(FILE *pstFile, uint32 *pulFileSize)
{
    bool blFunctionStatus = false;

    if ((NULL != pstFile) && (NULL != pulFileSize))
    {
        fseek(pstFile, 0, SEEK_END);
        *pulFileSize = ftell(pstFile);
        fseek(pstFile, 0, SEEK_SET);
        blFunctionStatus = true;
    }
    else
    {
        printf("Input pointers are NULL\n");
    }

    return blFunctionStatus;
}

//**********************.fileOperationFindExtension.****************************
// Purpose : Find out the extension of a given file.
// Inputs  : pcFileName - file name pointer.
// Outputs : ppcExtension - extension address pointer.
//           pblExtensionStatus - extension status pointer.
// Return  : True if extension found out successfully, else false.
// Notes   : None.
//******************************************************************************
bool fileOperationFindExtension(char *pcFileName, char **ppcExtension,
                                bool *pblExtensionStatus)
{
    bool blFunctionStatus = false;
    char *cExtension = NULL;

    if ((NULL != pcFileName) && (NULL != ppcExtension ))
    {
        cExtension = strchr(pcFileName, EXTENSION_SEPARATION);

        if (cExtension != NULL)
        {
            cExtension ++;
            *ppcExtension = cExtension;

            if (NULL != pblExtensionStatus)
            {
                *pblExtensionStatus = true;
            }
    
            blFunctionStatus = true;
        }
        else
        {
            *pblExtensionStatus = false;
            blFunctionStatus = true;
        }
    }
    else
    {
        printf("Cannot Find Extension: Input pointers is NULL\n");
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF