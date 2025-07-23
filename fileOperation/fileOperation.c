//**************************** FileOperations **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : fileOperation.c
// Summary : Contains the functions for file operations.
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
// Inputs  : pcFileName - file name.
//           pstMode - mode to open the file.
// Outputs : pstFile - pointer to the opened file.
// Return  : True if file opened successfully else false.
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
        printf("Input pointer is NULL");
    }

    return blFunctionStatus;
}

//*************************.fileOperationClose.*********************************
// Purpose : Close the file.
// Inputs  : pstFile - Pointer to the file.
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
// Purpose : Determine the size of file.
// Inputs  : pstFile - file pointer.
// Outputs : pulFileSize - Pointer to the size variable.
// Return  : True if size variable updated, else false.
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
        printf("Input pointer are NULL");
    }

    return blFunctionStatus;
}

//****************************.fileOperationCopy.*******************************
// Purpose : Copy contents from a file to another file.
// Inputs  : pstFile - file pointer.
//           ulFileSize - size of the file.
// Outputs : pstOutputFile - copy file pointer.
// Return  : True if file contents copied successfully, else false.
// Notes   : None.
//******************************************************************************
bool fileOperationCopy(uint32 ulFileSize, FILE *pstFile, FILE *pstOutputFile)
{
    bool blFunctionStatus = false;
    void *pFileStorage = NULL;
    uint32 ulFileCharacterCount = 0;
    uint32 ulTotalCopyCount = 0;

    if ((NULL != pstFile) && (NULL != pstOutputFile))
    {
        pFileStorage = malloc(ulFileSize);

        if (pFileStorage != NULL)
        {
            while ((ulFileCharacterCount = fread(pFileStorage, SIZE,
                                                 sizeof(pFileStorage),
                                                 pstFile)) > 0)
            {
                fwrite(pFileStorage, SIZE, ulFileCharacterCount, pstOutputFile);
                ulTotalCopyCount += ulFileCharacterCount;
            }

            if (ulFileSize == ulTotalCopyCount)
            {
                blFunctionStatus = true;
            }
            else
            {
                printf("Copying Failed\n");
            }
        }
        else
        {
            printf("Memory allocation failed\n");
        }
    }

    free(pFileStorage);
    pFileStorage = NULL;

    return blFunctionStatus;
}
//******************************************************************************
// EOF