//****************************** ListFiles *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : listFiles.c
// Summary : Contains the program to link and list all the files in a directory.
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
bool listFilesCreatePath(char *pcFileName, char *pcPath, char **ppcFullPath);
bool listFilesAccessEach(struct dirent *pstDirectoryContents,
                         char *pcDirectoryPath, FILE_DETAILS **ppstHeadNode);
bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 pulSize,
                       FILE_DETAILS **ppstHeadNode);
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 pulSize,
                         FILE_DETAILS **ppstNode);
bool listFilesPrint(FILE_DETAILS **ppstHeadNode);
bool listFilesFreeLink(FILE_DETAILS **ppstHeadNode);

//****************************.listFilesCheckDirectory.*************************
// Purpose : To open the directory and checkout the files inside and list them.
// Inputs  : pcDirectoryPath - Pointer to the path of directory.
// Outputs : None.
// Return  : True if directory opened successfully and files listed else, false.
// Notes   : None.
//******************************************************************************
bool listFilesCheckDirectory(char *pcDirectoryPath)
{
    bool blFunctionStatus = false;
    DIR *pstDirectoryPointer = NULL;
    struct dirent *pstDirectoryContents = NULL;
    FILE_DETAILS *pstHeadNode = NULL;

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

        if ((NULL == pstDirectoryPointer) && (NULL == pstDirectoryContents))
        {
            printf("Invalid directory: Cannot be opened");
            break;
        }

        while (NULL != (pstDirectoryContents = readdir(pstDirectoryPointer)))
        {
            if (FILE_TYPE == (pstDirectoryContents)->d_type)
            {
                listFilesAccessEach(pstDirectoryContents, pcDirectoryPath, 
                                    &pstHeadNode);
            }
        }

        if (false == listFilesPrint(&pstHeadNode))
        {
            printf("Cannot print the list");
            break;
        }

        

        // after the while loop ends, all files arre linked then jus print the link.

        blFunctionStatus = true;

    } while (blFunctionStatus == false);

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
                         char *pcDirectoryPath, FILE_DETAILS **ppstHeadNode)
{
    FILE *pstFilePointer = NULL;
    uint32 ulFileSize = 0;
    char *pcFullPath = NULL;
    int8 *pcNameOfFile = NULL;
    int8 *pcFileName = NULL;
    int8 *pcExtension = NULL;
    bool blExtensionStatus = false;
    bool blFunctionStatus = false;
    bool blFullPathExist = false;

    if ((NULL != pstDirectoryContents) && (NULL != pcDirectoryPath) &&
        (NULL != ppstHeadNode))
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

            blFullPathExist = true;

            if (false == fileOperationOpen(&pstFilePointer, pcFullPath, READ))
            {
                printf("Cannot open file: %s\n", pcFullPath);
                break;
            }

            if (false == fileOperationSize(pstFilePointer, &ulFileSize))
            {
                printf("Cannot get size for file: %s\n", pcFullPath);
                fileOperationClose(pstFilePointer);
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

        } while (blFunctionStatus == false);

        if (true == blFullPathExist)
        {
            free(pcFullPath);
            pcFullPath = NULL; 
        }
    }

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

//*************************.listFilesLinkNode.**********************************
// Purpose : Create new nodes and link them accordingly.
// Inputs  : pcName - Pointer to the name of file.
//           pcExtension - Pointer to the file extension.
//           pulSize - Pointer to the size of the file.
//           ppstHeadNode - pointer to the head node of the linked list.
// Outputs : None
// Return  : True if successfully created link, else false.
// Notes   : None.
//******************************************************************************
bool listFilesLinkNode(int8 *pcName, int8 *pcExtension, uint32 pulSize,
                       FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstNewNode = NULL;
    FILE_DETAILS *pstCurrentNode = NULL;

    if ((NULL != pcName) && (NULL != pcExtension) && (NULL != ppstHeadNode))
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
bool listFilesCreateNode(int8 *pcName, int8 *pcExtension, uint32 pulSize,
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

            (*ppstNewNode)->ucFileType = malloc(strlen((char *)pcExtension) + 1);

            if (NULL != (*ppstNewNode)->ucFileType)
            {
                strcpy((char *)(*ppstNewNode)->ucFileType, (char *)pcExtension);
            }

            (*ppstNewNode)->ulFileSize = pulSize;
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
// Purpose : To print the linked list.
// Inputs  : None.
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

        if (NULL != pstCurrentNode)
        {
            while (pstCurrentNode != NULL)
            {
                printf("File Name: %s,         File Type: %s",
                                                pstCurrentNode->ucFileName,
                                                pstCurrentNode->ucFileType);
                printf("           File Size: %lu bytes\n\n",
                                                 pstCurrentNode->ulFileSize);
                pstCurrentNode = pstCurrentNode->pstNext;
            }
        }

        if (true == listFilesFreeLink(ppstHeadNode))
        {
            blFunctionStatus = true;
        }
    }

    return blFunctionStatus;
}

//*************************.listFilesFreeLink.**********************************
// Purpose : To free the linked list.
// Inputs  : ppstHeadNode - Double pointer to the head node.
// Outputs : None.
// Return  : True if successfully freed the the linked list, else false.
// Notes   : None.
//******************************************************************************
bool listFilesFreeLink(FILE_DETAILS **ppstHeadNode)
{
    bool blFunctionStatus = false;
    FILE_DETAILS *pstCurrentNode =  NULL;
    FILE_DETAILS *pstNode = NULL;

    if (NULL != ppstHeadNode)
    {
        pstNode = *ppstHeadNode;

        while (NULL != pstNode)
        {
            pstCurrentNode = pstNode;
            pstNode = pstNode->pstNext;
            free(pstCurrentNode);
        }

        blFunctionStatus = true;
    }

    return blFunctionStatus;
}
//******************************************************************************
// EOF