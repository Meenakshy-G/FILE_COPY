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
// Purpose : To copy contents from source file to destination file.
// Inputs  : pcFileName - pointer to the input file name
// Outputs : None.
// Return  : blFunctionStatus - True if copy of the file is created 
//           successfully else false.
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
// Purpose : To extract file name from path if path is given.
// Inputs  : pcFileNameDuplicate - Pointer to the duplicate file name.
// Outputs : pcInputFile pointer is updated to point file name only, by 
//           removing path, if path given.
// Return  : blFunctionStatus - True if path is successfully removed, 
//           else returns false.
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
// Purpose : To add extension to the copy file name.
// Inputs  : pcInputFileName - Pointer to the input file name.
//           ppcOutputFileName - Double pointer to the duplicate file name.
// Outputs : ppcOutputFileName is updated with modified output name.
// Return  : blFunctionStatus - True if extension is successfully added, 
//           else returns false.
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
// Purpose : To form the final output file name.
// Inputs  : pcExtension - Pointer to the original extension.
//           ppcInputFileName - Pointer to the file name to be modified.
// Outputs : ppcOutputFile - Pointer is updated to the modified file name.
// Return  : blFunctionStatus - True if name is successfully modified, 
//           else returns false.
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
// Purpose : To copy the file contents and close the files.
// Inputs  : pstFilePointer - Pointer to the input file.
//           pcOutputFileName - Pointer to the output file name.
//           pulFileSize - Pointer to the size of the file.
// Outputs : None
// Return  : blFunctionStatus - True if copying is successfull, 
//           else returns false.
// Notes   : None
//******************************************************************************
bool fileCopyPerformFileCopy(FILE *pstFilePointer,char *pcOutputFileName, 
                             uint32 pulFileSize)
{
    FILE *pstOutputFilePointer = NULL;
    bool blFunctionStatus = false;

    if ((NULL != pstFilePointer) && (NULL != pcOutputFileName))
    {
        if (true == fileOperationOpen(&pstOutputFilePointer,
                                      pcOutputFileName, WRITE_MODE))
        {
            if (true == fileOperationCopy(pulFileSize, pstFilePointer,
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
