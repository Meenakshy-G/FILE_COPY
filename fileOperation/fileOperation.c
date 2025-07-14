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

//****************************.FileOperationOpenFile.***************************
// Purpose : To open the file in read or write mode.
// Inputs  : Pointer to the file, file name and the mode to open.
// Outputs : Pointer updated to the opened file.
// Return  : True if success else false.
// Notes   : None
//******************************************************************************
bool FileOperationOpenFile(FILE **pstFile, 
                           uint8 *pstFileName, uint8 *pstMode)
{
    bool blFunctionStatus = true;
    *pstFile = fopen(pstFileName, pstMode);

    if (pstFile == NULL)
    {
        perror("Error opening the file");
        fclose(*pstFile);
        blFunctionStatus = false;
    }

    return blFunctionStatus;
}

//*************************.FileOperationCloseFile.*****************************
// Purpose : To close the already opened files.
// Inputs  : Pointer to the file.
// Outputs : None
// Return  : True for success else false.
// Notes   : None
//******************************************************************************
bool FileOperationCloseFile(FILE *pstFile)
{
    bool blFunctionStatus = true;

    if (fclose(pstFile) != 0)
    {
        perror("Error closing the file");
        blFunctionStatus = false;
    }

    return blFunctionStatus;
}

//***************************.FileOperationFileSize.****************************
// Purpose : To find out the size of input file. 
// Inputs  : File pointer and the pointer to size variable.
// Outputs : None
// Return  : True for successful completion.
// Notes   : None
//******************************************************************************
bool FileOperationFileSize(FILE *pstFile, uint32 *pulFileSize)
{
    fseek(pstFile, 0, SEEK_END);
    *pulFileSize = ftell(pstFile);
    fseek(pstFile, 0, SEEK_SET);

    return true;
}

//****************************.FileOperationCopyContent.************************
// Purpose : To copy contents from source file to destination file.
// Inputs  : Source file pointer, destination file pointer, size fo file.
// Outputs : None.
// Return  : True for success else false.
// Notes   : None
//******************************************************************************
bool FileOperationCopyContent(uint32 *pulFileSize, FILE *pstFile, 
                              FILE *pstCopyFile )
{
    bool blFunctionStatus = true;
    void *pulFileStorage  = NULL;
    uint32 ulFileCharacterCount = 0;
    uint32 ulTotalCopyCount = 0;

    pulFileStorage = malloc(*pulFileSize);

    if (!pulFileStorage) 
    {
        perror("Memory allocation failed");
        blFunctionStatus = false;
    }

    while ((ulFileCharacterCount = fread(pulFileStorage, SIZE, 
                                         sizeof(pulFileStorage), pstFile)) > 0)
    {
        fwrite(pulFileStorage, SIZE, ulFileCharacterCount, pstCopyFile);
        ulTotalCopyCount += ulFileCharacterCount;
    }

    if (*pulFileSize != ulTotalCopyCount)
    {
        perror("Error in copying the file");
        blFunctionStatus = false;
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF