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
// Purpose : To call file operation functions to generate copy of the file.
// Inputs  : The file for which copy is to be generated.
// Outputs : The copy of the file is created.
// Return  : Zero for successful execution.
// Notes   : None
//******************************************************************************
int main(int argc, char *argv[])
{
    char *pcFileName = NULL;

    if (argc == INPUT_ARGUMENTS)
    {
        pcFileName = (char *)argv[FIRST_ARGUMENT];
        fileCopyTool(pcFileName);
    }
    else
    {
        printf("No Command Line Arguments Given\n");
    }

    return 0;
}
//******************************************************************************
// EOF