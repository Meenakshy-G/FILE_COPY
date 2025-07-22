//**************************** FileCopyApp *************************************
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
#include "listFiles.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
// Purpose : To get the input directory path from command line argument and 
//           forward it to listFiles.c file to generate the list of files in it. 
// Inputs  : The command line argument of directory path pointed by
//           pcDirectoryPath.
// Outputs : None.
// Return  : Zero.
// Notes   : None.
//******************************************************************************
int main(int argc, char *argv[])
{
    char *pcDirectoryPath = NULL;

    if (INPUT_ARGUMENTS == argc)
    {
        pcDirectoryPath = (char *)argv[FIRST_ARGUMENT];

        if (NULL != pcDirectoryPath)
        {
            if (true == listFilesCheckDirectory(pcDirectoryPath))
            {
                printf("Files listed succesfully\n");
            }
        }
        else
        {
            printf("Cannot obtain input path argument\n");
        }
    }
    else
    {
        printf("No Command Line Arguments Given\n");
    }

    return 0;
}
//******************************************************************************
// EOF