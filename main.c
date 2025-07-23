//**************************** FileCopyApp *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.c
// Summary : Contains program to list all files in a given directory.
// Note    : Header files are included.
// Author  : Meenakshy G
// Date    : 18/JULY/2025
//******************************************************************************
//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "common.h"
#include "fileOperation.h"
#include "directoryOperation.h"
#include "listFiles.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
// Purpose : List all files inside the given directory path.
// Inputs  : argc - Input argument count.
//           argv[] - Input directory path.
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
        printf("No Proper Command Line Arguments Given\n");
    }

    return 0;
}
//******************************************************************************
// EOF