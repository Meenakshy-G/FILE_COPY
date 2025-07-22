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
// Purpose : To open the file in read or write mode.
// Inputs  : pstFile - Pointer to the file.
//           pcFileName - file name.
//           pstMode - mode to open the file.
// Outputs : File pointer pstFile updated to point the opened file.
// Return  : blFunctionStatus - True if file opened succesfully, else false.
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
// Purpose : To close the already opened files.
// Inputs  : pstFile - Pointer to the file.
// Outputs : None.
// Return  : blFunctionStatus - True if file closed successfully, else false.
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
// Purpose : To find out the size of input file.
// Inputs  : pstFile - File pointer.
//           pulFileSize - Pointer to size variable.
// Outputs : None.
// Return  : blFunctionStatus - True if size variable updated, else false.
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
// Purpose : To find out the extension of input file.
// Inputs  : pcFileName - Pointer to input file name.
//           ppcExtension - Double pointer to the extension.
//           pblExtensionStatus - Pointer to the status of file extension.
// Outputs : The pointer to extension pstExtension updated with the 
//           extension of current file.
//           pblExtensionStatus - Pointer updated and value is set true if no 
//           extension to current file 
// Return  : blFunctionStatus - True if extension found out  successfully, 
//           else false.
// Notes   : None.
//******************************************************************************
bool fileOperationFindExtension(char *pcFileName, char **ppcExtension,
                                bool *pblExtensionStatus)
{
    bool blFunctionStatus = false;
    // printf("inhere: THe FIleNAME is : %s\n", pcFileName);
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

//****************************.fileOperationCopy.*******************************
// Purpose : To copy contents from source file to destination file.
// Inputs  : pstFile - Source file pointer.
//           pstOutputFile - destination file pointer.
//           pulFileSize - size fo file.
// Outputs : None.
// Return  : blFunctionStatus - True if file contents copied successfully, 
//           else false.
// Notes   : None.
//******************************************************************************
bool fileOperationCopy(uint32 *pulFileSize, FILE *pstFile, FILE *pstOutputFile)
{
    bool blFunctionStatus = false;
    void *pFileStorage = NULL;
    uint32 ulFileCharacterCount = 0;
    uint32 ulTotalCopyCount = 0;

    if ((NULL != pulFileSize) && (NULL != pstFile) && (NULL != pstOutputFile))
    {
        pFileStorage = malloc(*pulFileSize);

        if (pFileStorage != NULL)
        {
            while ((ulFileCharacterCount = fread(pFileStorage, SIZE,
                                                 sizeof(pFileStorage),
                                                 pstFile)) > 0)
            {
                fwrite(pFileStorage, SIZE, ulFileCharacterCount, pstOutputFile);
                ulTotalCopyCount += ulFileCharacterCount;
            }

            if (*pulFileSize == ulTotalCopyCount)
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