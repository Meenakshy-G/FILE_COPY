//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : fileCopy.c
// Summary : The helper file to assist in the file copy process.
// Note    : Contains functions that calls the file operation functions. 
//           Header file included.
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
bool fileCopyFrameOutputName(char **ppcOutputFile,
                             char *pcExtension, char **ppcInputFileName);
bool fileCopyExtractNameFromPath(char **pcInputFile, char *pcFileNameDuplicate);
bool fileCopyModifyExtension(char *pcInputFileName, char **ppcOutputFileName);
bool fileCopyPerformFileCopy(FILE *pstFilePointer,char *pcOutputFileName, 
                             uint32 pulFileSize);

//******************************.fileCopyTool.**********************************
// Purpose : Handle file operation functions to generate copy of a file.
// Inputs  : pcFileName - pointer to the input file path.
// Outputs : None.
// Return  : True if copy file created successfully else false.
// Notes   : None
//******************************************************************************
bool fileCopyTool(char *pcFileName)
{
    bool blFunctionStatus = false;
    FILE *pstFilePointer = NULL;
    uint32 ulFileSize = 0;
    char *pcFileNameDuplicate = NULL;
    char *pcInputFileName = NULL;
    char *pcOutputFileName = NULL;
    bool blCheckDuplicateNameExist = false;
    bool blCheckOutputNameExist = false;

    do
    {
        if (NULL == pcFileName)
        {
            printf("Input file name is NULL\n");
            break;
        }

        pcFileNameDuplicate = strdup(pcFileName);
        blCheckDuplicateNameExist = true;

        if (NULL == pcFileNameDuplicate)
        {
            printf("Failed to duplicate file name\n");
            blCheckDuplicateNameExist = false;
            break;
        }

        if (false == fileOperationOpen(&pstFilePointer, pcFileName, READ_MODE))
        {
            printf("Invalid or Incorrect file Name\n");
            break;
        }

        if (false == fileOperationSize(pstFilePointer, &ulFileSize))
        {
            printf("Failed to get file size\n");
            break;
        }

        if (false == fileCopyExtractNameFromPath(&pcInputFileName,
                                        pcFileNameDuplicate))
        {
            printf("Failed to extract file name from path\n");
            break;
        }

        if (false == fileCopyModifyExtension(pcInputFileName,
                                             &pcOutputFileName))
        {
            printf("Failed to form output file name\n");
            blCheckOutputNameExist = true;
            break;
        }

        if (false == fileCopyPerformFileCopy(pstFilePointer, pcOutputFileName, 
                                             ulFileSize))
        {
            printf("Failed to perform file copy\n");
            blCheckOutputNameExist = true;
            break;
        }

        blCheckOutputNameExist = true;
        blFunctionStatus = true;

    } while (blFunctionStatus == false);

    // free the dynamic memory allocated using strdup.
    if (true == blCheckDuplicateNameExist)
    {
        free(pcFileNameDuplicate);
        pcFileNameDuplicate = NULL;
    }

    // free the dynamic memory allocated using malloc.
    if (true == blCheckOutputNameExist)
    {
        free(pcOutputFileName);
        pcOutputFileName = NULL;
    }

    return blFunctionStatus;
}

//************************.fileCopyExtractNameFromPath.*************************
// Purpose : Extract the file name from input file path.
// Inputs  : pcFileNameDuplicate - file path pointer.
// Outputs : pcInputFile - file name pointer.
// Return  : True if file name extracted successfully, else false.
// Notes   : None
//******************************************************************************
bool fileCopyExtractNameFromPath(char **pcInputFile, char *pcFileNameDuplicate)
{
    bool blFunctionStatus = false;

    if (NULL != pcFileNameDuplicate)
    {
        *pcInputFile = strrchr(pcFileNameDuplicate, FOLDER_SEPARATION);

        if (NULL != *pcInputFile)
        {
            (*pcInputFile)++;
        }
        else
        {
            *pcInputFile = pcFileNameDuplicate;
        }

        if (NULL != *pcInputFile)
        {
            blFunctionStatus = true;
        }
    }

    return blFunctionStatus;
}

//************************.fileCopyModifyExtension.*****************************
// Purpose : Modify name and extension of input file.
// Inputs  : pcInputFileName - Input file name pointer.
// Outputs : ppcOutputFileName - modified file name pointer.
// Return  : True if file name modified successfully, else false.
// Notes   : None
//******************************************************************************
bool fileCopyModifyExtension(char *pcInputFileName, char **ppcOutputFileName)
{
    bool blFunctionStatus = false;
    uint32 ulLength = 0;
    char *pcExtension = NULL;

    if ((NULL != pcInputFileName) && (NULL != ppcOutputFileName))
    {
        pcExtension = strchr(pcInputFileName, EXTENSION_SEPARATION);

        if (pcExtension != NULL)
        {
            if (true == fileCopyFrameOutputName(ppcOutputFileName,
                                                pcExtension,
                                                &pcInputFileName))
            {
                blFunctionStatus = true;
            }
        }
        else
        {
            ulLength = strlen(pcInputFileName) + strlen(MODIFIER) + 1;
            *ppcOutputFileName = (char *)malloc(ulLength);

            if (*ppcOutputFileName != NULL)
            {
                strcpy(*ppcOutputFileName, pcInputFileName);
                strcat(*ppcOutputFileName, MODIFIER);
                blFunctionStatus = true;
            }
            else
            {
                printf("Memory allocation failed\n");
            }
        }
    }

    return blFunctionStatus;
}

//************************.fileCopyFrameOutputName.*****************************
// Purpose : Add modifier and extension to output file name.
// Inputs  : pcExtension - extension pointer.
//           ppcInputFileName - file name pointer.
// Outputs : ppcOutputFile - modified file name pointer.
// Return  : True if name is successfully modified, else false.
// Notes   : None
//******************************************************************************
bool fileCopyFrameOutputName(char **ppcOutputFile, char *pcExtension, 
                             char **ppcInputFileName)
{
    bool blFunctionStatus = false;
    uint32 ulNameLength = 0;
    uint32 ulExtensionLength = 0;
    uint32 ulTotalLength = 0;
    char *pcExtensionPosition = NULL;

    if((NULL != pcExtension) && (NULL != *ppcInputFileName))
    {
        pcExtensionPosition = strchr(*ppcInputFileName, EXTENSION_SEPARATION);

        if (pcExtensionPosition != NULL)
        {
            ulNameLength = (uint32)(pcExtensionPosition - *ppcInputFileName);
            ulExtensionLength = strlen(pcExtension);
            ulTotalLength = ulNameLength + strlen(MODIFIER) + 
                            ulExtensionLength + 1;
            *ppcOutputFile = (char *)malloc(ulTotalLength);

            if (*ppcOutputFile != NULL)
            {
                strncpy(*ppcOutputFile, *ppcInputFileName, ulNameLength);
                strcat(*ppcOutputFile, MODIFIER);
                strcat(*ppcOutputFile, pcExtension);
                blFunctionStatus = true;
            }
            else
            {
                printf("Memory allocation failed\n");
            }
        }
        else
        {
            printf("Cannot find extension\n");
        }
    }
    else
    {
        printf("Cannot frame output name\n");
    }

    return blFunctionStatus;
}

//************************.fileCopyPerformFileCopy.*****************************
// Purpose : Copy the contents from a file to new file.
// Inputs  : pstFilePointer - file pointer
//           pcOutputFileName - file name pointer.
//           ulFileSize - file size.
// Outputs : None
// Return  : True if successfully copied the file contents else false.
// Notes   : None
//******************************************************************************
bool fileCopyPerformFileCopy(FILE *pstFilePointer,char *pcOutputFileName, 
                             uint32 ulFileSize)
{
    FILE *pstOutputFilePointer = NULL;
    bool blFunctionStatus = false;

    if ((NULL != pstFilePointer) && (NULL != pcOutputFileName))
    {
        if (true == fileOperationOpen(&pstOutputFilePointer,
                                      pcOutputFileName, WRITE_MODE))
        {
            if (true == fileOperationCopy(ulFileSize, pstFilePointer,
                                          pstOutputFilePointer))
            {
                if ((true == fileOperationClose(pstFilePointer)) &&
                    (true == fileOperationClose(pstOutputFilePointer)))
                {
                    blFunctionStatus = true;
                }
                else
                {
                    printf("Cannot close file\n");
                }
            }
            else
            {
                printf("Cannot Copy File\n");
            }
        }
        else
        {
            printf("Failed to open output file\n");
        }
    }
    else
    {
        printf("Failed to perform file copy: Invalid Pointers\n");
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF
