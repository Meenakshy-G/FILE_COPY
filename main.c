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
#include "fileCopy.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
// Purpose : Generate copy of file from given file path. 
// Inputs  : argc - Input arguments count.
//           argv[] - Input file path.
// Outputs : None.
// Return  : Zero.
// Notes   : None
//******************************************************************************
int main(int argc, char *argv[])
{
    char *pcFileName = NULL;

    if (INPUT_ARGUMENTS == argc)
    {
        pcFileName = (char *)argv[FIRST_ARGUMENT];

        if (NULL != pcFileName)
        {
            if (true == fileCopyTool(pcFileName))
            {
                printf("File Copy Created Successfully\n");
            }
            else
            {
                printf("Cannot Create File copy\n");
            }
        }
        else
        {
            printf("Cannot obtain input file argument\n");
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