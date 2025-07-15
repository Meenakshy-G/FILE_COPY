//**************************** FileCopy ****************************************
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
#include "fileCopy.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
bool fileCopyFrameOutputName(char **pcOutputFile,
                             char *pcExtension, char **pcInputFileName);

//******************************.fileCopyTool.**********************************
// Purpose : To copy contents from source file to destination file.
// Inputs  : pcFileName - pointer to the input file name
//           pcFileNameDuplicate - pointer to the copy file name.
// Outputs : None.
// Return  : True if copy of the file is created else false
// Notes   : None
//******************************************************************************
bool fileCopyTool(char *pcFileName, char *pcFileNameDuplicate)
{
    FILE *pstFilePointer = NULL;
    FILE *pstOutputFilePointer = NULL;
    uint32 ulFileSize = 0;
    char *pcInputFileName = NULL;
    char *pcExtension = NULL;
    char *pcOutputFileName = NULL;

    if (!(fileOperationOpen(&pstFilePointer, pcFileName, "rb")))
    {
        printf("Incorrect file name or file does not exist\n");
    }
    else
    {
        fileOperationSize(pstFilePointer, &ulFileSize);

        if (strchr(pcFileNameDuplicate, FOLDER_SEPARATION) == NULL)
        {
            pcInputFileName = pcFileNameDuplicate;
        }
        else
        {
            pcInputFileName = strrchr(pcFileNameDuplicate, FOLDER_SEPARATION);

            if (pcInputFileName != NULL)
            {
                pcInputFileName++;
            }
        }

        if (!pcInputFileName)
        {
            printf("Cannot extract file name from path");
        }
        else
        {
            if ((pcExtension = strrchr(pcInputFileName,
                                       EXTENSION_SEPARATION)) != NULL)
            {
                fileCopyFrameOutputName(&pcOutputFileName,
                                        pcExtension,
                                        &pcInputFileName);

                if (pcOutputFileName == NULL)
                {
                    printf("Here the output file name is not formed");
                }
            }
            else
            {
                pcOutputFileName = strcat(pcInputFileName, (char *)MODIFIER);
            }
        }

        if (!(fileOperationOpen(&pstOutputFilePointer,
                                pcOutputFileName, "wb")))
        {
            printf("failed to open file");
        }
        fileOperationCopy(&ulFileSize, pstFilePointer, pstOutputFilePointer);
        fileOperationClose(pstFilePointer);
        fileOperationClose(pstOutputFilePointer);
    }
    return true;
}

//************************.fileCopyFrameOutputName.*****************************
// Purpose : To find file name if path is given.
// Inputs  : pcOutputFileName - Pointer to the modified file name.
//           pcExtension - Pointer to the original extension.
//           pcInputFileName - The file name to be modified.
// Outputs : Pointer to the modified file name is updated.
// Return  : True if name is successfully modified, else returns false.
// Notes   : None
//******************************************************************************
bool fileCopyFrameOutputName(char **pcOutputFile,
                             char *pcExtension, char **pcInputFileName)
{
    char *pcIntermediateName = NULL;
    char *pcRemoveExtension = NULL;
    char *pcExtensionCopy = NULL;

    pcExtensionCopy = strdup(pcExtension);
    pcRemoveExtension = strrchr(*pcInputFileName, EXTENSION_SEPARATION);
    *pcRemoveExtension = '\0';

    if ((pcIntermediateName = strcat(*pcInputFileName,
                                     MODIFIER)) != NULL)
    {

        if (pcExtensionCopy != NULL)
        {
            *pcOutputFile = strcat(pcIntermediateName, pcExtensionCopy);
        }
    }

    if (*pcOutputFile == NULL)
    {
        printf("Output file name cannot be assigned");
    }

    return true;
}
//******************************************************************************
// EOF