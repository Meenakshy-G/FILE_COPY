//****************************** ListFiles *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : listFiles.c
// Summary :
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
#include "directoryOperation.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
bool listFilesCreatePath(char *pcFileName, char *pcPath, char **pcFullPath);
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 *pulSize, 
                         FILE_DETAILS **pstNode);
bool listFilesAccessEach(struct dirent *pstDirectoryContents, 
                         char *pcDirectoryPath);
bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 *pulSize, 
                         FILE_DETAILS **ppstHeadNode);

//****************************.listFilesCheckDirectory.*************************
// Purpose :
// Inputs  :
// Outputs :
// Return  :
// Notes   : None.
//******************************************************************************
bool listFilesCheckDirectory(char *pcDirectoryPath)
{
    bool blFunctionStatus = false;
    DIR *pstDirectoryPointer = NULL;
    struct dirent *pstDirectoryContents;

    do
    {
        if (NULL == pcDirectoryPath)
        {
            printf("Invalid Directory pointer");
            break;
        }

        if (false == directoryOperationOpen(&pstDirectoryPointer,
                                            &pcDirectoryPath,
                                            &pstDirectoryContents))
        {
            printf("Cannot list files\n");
            break;
        }

        if ((NULL == pstDirectoryPointer) && (NULL == pstDirectoryContents))
        {
            printf("Invalid directory: Cannot be opened");
            break;
        }

        // make this things into another function.
        while (NULL != (pstDirectoryContents = readdir(pstDirectoryPointer)))
        {
            if (FILE_TYPE == (pstDirectoryContents)->d_type)
            {
                listFilesAccessEach(pstDirectoryContents, pcDirectoryPath);
            }
        }

        // after the while loop ends, all files arre linked then jus print the link.

        blFunctionStatus = true;

    } while (blFunctionStatus == false);


    return blFunctionStatus;
}

//*************************.listFilesCreatePath.********************************
// Purpose : To merge the obtained filename with directory path to get
//           complete file path.
// Inputs  : pcFileName - Pointer to the file name.
//           pcPath - Pointer to the directory path.
//           pcFullPath - Pointer to update the final merged file path.
// Outputs : pcFullPath - Pointer updated with the merged file path.
// Return  : blFunctionStatus - True if successfully merged the filename and
//           path, else false.
// Notes   : None.
//******************************************************************************
bool listFilesCreatePath(char *pcFileName, char *pcPath, char **pcFullPath)
{
    bool blFunctionStatus = false;
    uint32 ulPathLength = 0;

    if ((NULL != pcFileName) && (NULL != pcPath))
    {
        ulPathLength = strlen(pcFileName) + strlen(FILE_SEPARATOR) + 
                       strlen(pcPath) + 1;
        *pcFullPath = (char *)malloc(ulPathLength);

        if (NULL != *pcFullPath)
        {
            strcat(*pcFullPath, pcPath);
            strcat(*pcFullPath, FILE_SEPARATOR);
            strcat(*pcFullPath, pcFileName);
            blFunctionStatus = true;
        }
    }

    return blFunctionStatus;
}

//*************************.listFilesAccessEach.********************************
// Purpose : Perform the functions necessary to access each files.
// Inputs  : pstDirectoryContents - pointer to dirent struct for the file
//           pcDirectoryPath - directory path string
// Outputs : None
// Return  : True if successfully accessed each file, else false
// Notes   : None.
//******************************************************************************
bool listFilesAccessEach(struct dirent *pstDirectoryContents, 
                         char *pcDirectoryPath)
{
    FILE *pstFilePointer = NULL;
    uint32 ulFileSize = 0;
    char *pcFullPath = NULL;
    int8 *pcNameOfFile = NULL;
    int8 *pcFileName = NULL;
    char *pcExtension = NULL;
    bool blExtensionStatus = false;
    bool blFunctionStatus = false;
    FILE_DETAILS *pstHeadNode = NULL;

    if ((NULL != pstDirectoryContents) && (NULL != pcDirectoryPath))
    {
        do
        {
            pcFileName = (int8 *)pstDirectoryContents->d_name;

            if (NULL == pcFileName)
            {
                printf("Invalid file name \n");
                break;
            }

            if (false == listFilesCreatePath((char *)pcFileName,
                                             pcDirectoryPath, &pcFullPath))
            {
                printf("Cannot create full path for file: %s\n", pcFileName);
                break;
            }

            if (false == fileOperationOpen(&pstFilePointer, pcFullPath, READ))
            {
                printf("Cannot open file: %s\n", pcFullPath);
                free(pcFullPath);
                break;
            }

            if (false == fileOperationSize(pstFilePointer, &ulFileSize))
            {
                printf("Cannot get size for file: %s\n", pcFullPath);
                fileOperationClose(pstFilePointer);
                free(pcFullPath);
                break;
            }

            pcNameOfFile = (int8 *)pstDirectoryContents->d_name;

            if (NULL == pcNameOfFile)
            {
                printf("Invalid file name in directory entry\n");
                break;
            }

            if (false == fileOperationFindExtension((char *)pcNameOfFile,
                                                    &pcExtension,
                                                    &blExtensionStatus))
            {
                printf("Cannot find extension for file: %s\n", pcNameOfFile);
            }

            if (false == blExtensionStatus)
            {
                pcExtension = (char *)"No Extension";
            }

            listFilesLinkNode(pcNameOfFile, (int8 *)pcExtension, &ulFileSize, &pstHeadNode); 
                         

            // if (false == listFilesCreateNode(pcNameOfFile,
            //                                  (int8 *)pcExtension,
            //                                  &ulFileSize, &pstHeadNode))
            // {
            //     printf("Cannot create node for file: %s\n", pcNameOfFile);
            //     fileOperationClose(pstFilePointer);
            //     break;
            // }

            blFunctionStatus = true;

        } while (blFunctionStatus == false);
    }

    return blFunctionStatus;
}

//*************************.listFilesCreateNode.********************************
// Purpose : Perform the functions necessary to create nodes for each files.
// Inputs  : pcName - Pointer to the name of file.
//           pcExtension - Pointer to the file extension.
//           pulSize - Pointer to the size of the file.
//           ppstNewNode - pointer to the FILE_DETAILS struct.
// Outputs : None
// Return  : True if successfully accessed each file, else false
// Notes   : None.
//******************************************************************************
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 *pulSize, 
                         FILE_DETAILS **ppstNewNode)
{
    bool blFunctionStatus = false;

    if ((NULL != pcName) && (NULL != pcExtension) && (NULL != pulSize) && 
        (NULL != ppstNewNode))
    {
        *ppstNewNode = (FILE_DETAILS *)malloc(sizeof(FILE_DETAILS));

        if (NULL != *ppstNewNode)
        {
            (*ppstNewNode)->ucFileName = malloc(strlen((char *)pcName) + 1);

            if (NULL != (*ppstNewNode)->ucFileName)
            {
                strcpy((char *)(*ppstNewNode)->ucFileName, (char *)pcName);
            }

            (*ppstNewNode)->ucFileType = malloc(strlen((char *)pcExtension) + 1);

            if (NULL != (*ppstNewNode)->ucFileType)
            {
                strcpy((char *)(*ppstNewNode)->ucFileType, (char *)pcExtension);
            }

            (*ppstNewNode)->ulFileSize = *pulSize;
            (*ppstNewNode)->pstNext = NULL;

            blFunctionStatus = true;
        }
        else
        {
            printf("Memory allocation failed\n");
        }
    }

    return blFunctionStatus;
}


bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 *pulSize, 
                         FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstNewNode = NULL;
    FILE_DETAILS *pstCurrentNode = NULL;

    if ((NULL != pcName) && (NULL != pcExtension) && (NULL != pulSize) && 
        (NULL != ppstHeadNode))
    {
        listFilesCreateNode(pcName, pcExtension, pulSize, &pstNewNode); 

        if (*ppstHeadNode == NULL)
        {
            *ppstHeadNode = pstNewNode;
        }
        else
        {
            pstCurrentNode = *ppstHeadNode;

            while (NULL != pstCurrentNode->pstNext)
            {
                pstCurrentNode = pstCurrentNode->pstNext;
            }

            pstCurrentNode->pstNext = pstNewNode;
        }

        blFunctionStatus = true;
    }

    return blFunctionStatus
}
//******************************************************************************
// EOF