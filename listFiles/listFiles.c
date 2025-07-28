//****************************** ListFiles *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : listFiles.c
// Summary : Contains the program to sort and list all the files in a directory.
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

//****************************** Local Types ***********************************

//****************************** Local Constants *******************************

//****************************** Local Variables *******************************

//****************************** Local Functions *******************************
bool listFilesCreatePath(char *pcFileName, char *pcPath, char **ppcFullPath);
bool listFilesAccessEach(struct dirent *pstDirectoryContents, char *pcFullPath,
                         char *pcDirectoryPath, FILE_DETAILS **ppstHeadNode,
                         bool *blCheckFileOpen, FILE **pstFilePointer);
bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 ulSize,
                       FILE_DETAILS **ppstHeadNode);
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 ulSize,
                         FILE_DETAILS **ppstNode);
bool listFilesPrint(FILE_DETAILS **ppstHeadNode);
bool listFilesFreeLink(FILE_DETAILS **ppstHeadNode);

//****************************.listFilesCheckDirectory.*************************
// Purpose : Handle directory operations to list files in the directory.
// Inputs  : pcDirectoryPath - directory path pointer.
// Outputs : None.
// Return  : True if files listed successfully, else false.
// Notes   : None.
//******************************************************************************
bool listFilesCheckDirectory(char *pcDirectoryPath)
{
    bool blFunctionStatus = false;
    DIR *pstDirectoryPointer = NULL;
    struct dirent *pstDirectoryContents = NULL;
    FILE_DETAILS *pstHeadNode = NULL;
    bool blFullPathExist = false;
    char *pcFullPath = NULL;
    bool blCheckDirectoryOpen = false;
    bool blCheckFileOpen = false;
    FILE *pstFilePointer = NULL;

    do
    {
        if (NULL == pcDirectoryPath)
        {
            printf("Invalid Directory pointer");
            break;
        }

        if (false == directoryOperationOpen(&pstDirectoryPointer,
                                            &pcDirectoryPath))
        {
            printf("Cannot Open Directory\n");
            break;
        }

        blCheckDirectoryOpen = true;

        if ((NULL == pstDirectoryPointer) && (NULL == pstDirectoryContents))
        {
            printf("Invalid directory: Cannot be opened");
            break;
        }

        while (NULL != (pstDirectoryContents = readdir(pstDirectoryPointer)))
        {
            if (FILE_TYPE == (pstDirectoryContents)->d_type)
            {
                if (false == (listFilesAccessEach(pstDirectoryContents,
                                                  pcFullPath,
                                                  pcDirectoryPath,
                                                  &pstHeadNode,
                                                  &blCheckFileOpen,
                                                  &pstFilePointer)))
                {
                    printf("Cannot Access Each File\n");
                }
            }

            blFullPathExist = true;
        }

        if (false == listFilesPrint(&pstHeadNode))
        {
            printf("Cannot print the list");
            break;
        }

        blFunctionStatus = true;

    } while (false == blFunctionStatus);

    if (true == blFullPathExist)
    {
        free(pcFullPath);
        pcFullPath = NULL;
    }

    if (true == blCheckDirectoryOpen)
    {
       if (false == directoryOperationClose(&pstDirectoryPointer))
       {
            printf("Cannot Close Directory");
       }
    }

    if (true == blCheckFileOpen)
    {
        if (false == fileOperationClose(pstFilePointer))
        {
            printf("Cannot close file");
        }
    }

    return blFunctionStatus;
}

//*************************.listFilesAccessEach.********************************
// Purpose : Handle file Operations to access each files in the directory.
// Inputs  : pstDirectoryContents - directory contents pointer.
//           pcDirectoryPath - directory path pointer.
// Outputs : None
// Return  : True if successfully accessed each file, else false.
// Notes   : None.
//******************************************************************************
bool listFilesAccessEach(struct dirent *pstDirectoryContents, char *pcFullPath,
                         char *pcDirectoryPath, FILE_DETAILS **ppstHeadNode,
                         bool *blCheckFileOpen, FILE **pstFilePointer)
{
    uint32 ulFileSize = 0;
    int8 *pcNameOfFile = NULL;
    int8 *pcFileName = NULL;
    int8 *pcExtension = NULL;
    bool blExtensionStatus = false;
    bool blFunctionStatus = false;

    if ((NULL != pstDirectoryContents) && (NULL != pcDirectoryPath) &&
        (NULL != ppstHeadNode) && (NULL != pstFilePointer))
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

            if (false == fileOperationOpen(pstFilePointer, pcFullPath, READ))
            {
                printf("Cannot open file: %s\n", pcFullPath);
                break;
            }

            *blCheckFileOpen = true;

            if (false == fileOperationSize(*pstFilePointer, &ulFileSize))
            {
                printf("Cannot get size for file: %s\n", pcFullPath);
                break;
            }

            pcNameOfFile = (int8 *)pstDirectoryContents->d_name;

            if (NULL == pcNameOfFile)
            {
                printf("Invalid file name in directory entry\n");
                break;
            }

            if (false == fileOperationFindExtension((char *)pcNameOfFile,
                                                    (char **)&pcExtension,
                                                    &blExtensionStatus))
            {
                printf("Cannot find extension for file: %s\n", pcNameOfFile);
            }

            if (false == blExtensionStatus)
            {
                pcExtension = (int8 *)"No Extension";
            }

            if (false == listFilesLinkNode(pcNameOfFile, pcExtension,
                                           ulFileSize, ppstHeadNode))
            {
                printf("Cannot link the nodes\n");
                break;
            }

            blFunctionStatus = true;

        } while (false == blFunctionStatus);
    }

    return blFunctionStatus;
}

//*************************.listFilesCreatePath.********************************
// Purpose : Combine directory path with file name.
// Inputs  : pcFileName - file name pointer.
//           pcPath - directory path pointer.
// Outputs : pcFullPath - combined path pointer.
// Return  : True if successfully formed the full path, else false.
// Notes   : None.
//******************************************************************************
bool listFilesCreatePath(char *pcFileName, char *pcPath, char **ppcFullPath)
{
    bool blFunctionStatus = false;
    uint32 ulPathLength = 0;

    if ((NULL != pcFileName) && (NULL != pcPath))
    {
        ulPathLength = strlen(pcFileName) + strlen(FILE_SEPARATOR) +
                       strlen(pcPath) + 1;
        *ppcFullPath = (char *)malloc(ulPathLength);

        if (NULL != *ppcFullPath)
        {
            strcat(*ppcFullPath, pcPath);
            strcat(*ppcFullPath, FILE_SEPARATOR);
            strcat(*ppcFullPath, pcFileName);
            blFunctionStatus = true;
        }
    }

    return blFunctionStatus;
}

//*************************.listFilesLinkNode.**********************************
// Purpose : Create linked list of files.
// Inputs  : pcName - file name pointer.
//           pcExtension - extension pointer.
//           pulSize - size pointer.
// Outputs : None
// Return  : True if successfully created link, else false.
// Notes   : None.
//******************************************************************************
bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 ulSize,
                       FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstNewNode = NULL;
    FILE_DETAILS *pstCurrentNode = NULL;

    if ((NULL != pcName) && (NULL != pcExtension) && (NULL != ppstHeadNode))
    {
        if (true == listFilesCreateNode(pcName, pcExtension, ulSize, 
                                        &pstNewNode))
        {
            if ((NULL == *ppstHeadNode) || 
                (pstNewNode->ulFileSize < (*ppstHeadNode)->ulFileSize))
            {
                pstNewNode->pstNext = *ppstHeadNode;
                *ppstHeadNode = pstNewNode;
            }
            else
            {
                pstCurrentNode = *ppstHeadNode;

                while ((NULL != pstCurrentNode->pstNext) &&
                       (pstCurrentNode->pstNext->ulFileSize < 
                                                    pstNewNode->ulFileSize))
                {
                    pstCurrentNode = pstCurrentNode->pstNext;
                }

                pstNewNode->pstNext = pstCurrentNode->pstNext;
                pstCurrentNode->pstNext = pstNewNode;
            }
        }

        blFunctionStatus = true;
    }

    return blFunctionStatus;
}

//*************************.listFilesCreateNode.********************************
// Purpose : Create nodes for linked list.
// Inputs  : pcName - file name pointer.
//           pcExtension - extension pointer.
//           ulSize - size pointer.
// Outputs : None
// Return  : True if successfully created node for each file, else false
// Notes   : None.
//******************************************************************************
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 ulSize,
                         FILE_DETAILS **ppstNewNode)
{
    bool blFunctionStatus = false;

    if ((NULL != pcName) && (NULL != pcExtension) && (NULL != ppstNewNode))
    {
        *ppstNewNode = (FILE_DETAILS *)malloc(sizeof(FILE_DETAILS));

        if (NULL != *ppstNewNode)
        {
            (*ppstNewNode)->ucFileName = malloc(strlen((char *)pcName) + 1);

            if (NULL != (*ppstNewNode)->ucFileName)
            {
                strcpy((char *)(*ppstNewNode)->ucFileName, (char *)pcName);
            }

            (*ppstNewNode)->ucFileType = malloc(strlen
                                               ((char *)pcExtension) + 1);

            if (NULL != (*ppstNewNode)->ucFileType)
            {
                strcpy((char *)(*ppstNewNode)->ucFileType, (char *)pcExtension);
            }

            (*ppstNewNode)->ulFileSize = ulSize;
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

//*************************.listFilesPrint.*************************************
// Purpose : Print the linked list.
// Inputs  : ppstHeadNode - head of linked list pointer.
// Outputs : None.
// Return  : True if successfully printed the linked list, else false.
// Notes   : None.
//******************************************************************************
bool listFilesPrint(FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstCurrentNode = NULL;

    if (NULL != ppstHeadNode)
    {
        pstCurrentNode = *ppstHeadNode;

        while (pstCurrentNode != NULL)
        {
            
            *ppstHeadNode = (*ppstHeadNode)->pstNext;
            printf("File Name: %s,  File Type: %s", pstCurrentNode->ucFileName,
                                                    pstCurrentNode->ucFileType);
            printf("  File Size: %lu bytes\n\n", pstCurrentNode->ulFileSize);
            pstCurrentNode = pstCurrentNode->pstNext;
        }

        if (true == listFilesFreeLink(ppstHeadNode))
        {
            blFunctionStatus = true;
        }
    }

    return blFunctionStatus;
}

//*************************.listFilesFreeLink.**********************************
// Purpose : Free the linked list.
// Inputs  : ppstHeadNode - head of linked list pointer.
// Outputs : None.
// Return  : True if successfully freed the the linked list, else false.
// Notes   : None.
//******************************************************************************
bool listFilesFreeLink(FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstCurrentNode = NULL;
    FILE_DETAILS *pstNode = NULL;

    if (NULL != ppstHeadNode)
    {
        pstNode = *ppstHeadNode;

        while (NULL != pstNode)
        {
            pstCurrentNode = pstNode;
            pstNode = pstNode->pstNext;
            free(pstCurrentNode);
            pstCurrentNode = NULL;
        }

        blFunctionStatus = true;
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF