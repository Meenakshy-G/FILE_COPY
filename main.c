//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.c
// Summary : Contains program to generate duplicate of a given file.
// Note    : Header files are included.
// Author  : Meenakshy G
// Date    : 11/JULY/2025
//******************************************************************************
//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "common.h"
#include "fileOperation.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
// Purpose : To call file operation functions to generate copy of the file.
// Inputs  : The file for which copy is to generated.
// Outputs : The copy of the file is created.
// Return  : Zero for successful execution.
// Notes   : None
//******************************************************************************
int main(int argc, char *argv[])
{
    FILE *pstFilePointer                = NULL;
    FILE *pstCopyFilePointer            = NULL;
    const char *pucFile                  = NULL;
    const char *pucFileNameCopy          = NULL;
    const char *pucCopyFileName          = NULL;
    const char *pucCopyFile              = NULL;
    const char ucCharacterToSearch       = '.';
    const char ucNameModifier[]          = "_copy";
    const char *pucIntermediateName      = NULL;
    const char *pucExtension             = NULL;
    const char *pucExtensionCopy         = NULL;
    uint32 pulFileSize              = 0;
    uint16 unFunctionStatus         = 0;
    const char *pucModeRead              = "rb";
    const char *pucModeWrite             = "wb";

    if (argc != INPUT_ARGUMENTS)
    {
        perror("File not given");
        unFunctionStatus = 1;
    }
    pucFile = (const char*)argv[FIRST_ARGUMENT];
    pucFileNameCopy = strdup(pucFile);
    FileOperationOpenFile(&pstFilePointer, pucFile, pucModeRead);
    FileOperationFileSize(pstFilePointer, &pulFileSize);
    pucCopyFile = basename((char *)pucFileNameCopy);
    pucExtension = strrchr(pucCopyFile, ucCharacterToSearch);

    if (pucExtension)
    {
        pucExtensionCopy = strdup(pucExtension);
        *strrchr(pucCopyFile, ucCharacterToSearch) = '\0';
        pucIntermediateName = strcat((char *)pucCopyFile,
                                     (char *)ucNameModifier);
        pucCopyFileName = strcat((char *)pucIntermediateName,
                                 (char *)pucExtensionCopy);
    }
    else
    {
        pucCopyFileName = strcat((char *)pucCopyFile,(char *)ucNameModifier);
    }
    FileOperationOpenFile(&pstCopyFilePointer, pucCopyFileName, pucModeWrite);
    FileOperationCopyContent(&pulFileSize, 
                             pstFilePointer, pstCopyFilePointer);
    FileOperationCloseFile(pstFilePointer);
    FileOperationCloseFile(pstCopyFilePointer);

    return unFunctionStatus;
}
//******************************************************************************
// EOF