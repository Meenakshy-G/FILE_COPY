//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.c
// Summary : Contains program to generate duplicate of a given file.
// Note    : 
// Author  : Meenakshy G
// Date    : 11/JULY/2025
//******************************************************************************
//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include "common.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
// Purpose :  
// Inputs  : 
// Outputs : 
// Return  : None
// Notes   : None
//******************************************************************************
int main(uint16 argc, char *argv[])
{
    FILE *pstFilePointer            = NULL;
    FILE *pstDestinationFilePointer = NULL;
    uint8 *pucInputFileName         = NULL;
    uint8 *pucOutputFileName        = NULL;
    uint8 appendName[5]             = "copy";
    int32 ulEachCharacter           = 0;
    uint32 ulCharacterCount         = 0;
    uint32 ulCounter                = 0;
    uint8 ucExtensionStart          = '.';
    uint8 ucExtensionPosition;

    if(argc < 2)
    {
        printf("File not given");
    }
    pucInputFileName = (uint8*)argv[1];
    pstFilePointer = fopen(pucInputFileName, "r+");

    if(pstFilePointer == NULL)
    {
        printf("Error opening the file");
        fclose(pstFilePointer);
    }
    pucOutputFileName = strcat(appendName,pucInputFileName);
    // pucOutputFileName = strcat(pucInputFileName,"_copy");
    pstDestinationFilePointer = fopen(pucOutputFileName,"w+");

    if(pstDestinationFilePointer == NULL)
    {
        printf("Error opening the file");
        fclose(pstDestinationFilePointer);
    }

    while((ulEachCharacter = fgetc(pstFilePointer)) != EOF)
    {
        ulCharacterCount ++;
        fputc(ulEachCharacter, pstDestinationFilePointer);
        fseek(pstDestinationFilePointer,0,SEEK_CUR);
    }
    fclose(pstFilePointer);
    fclose(pstDestinationFilePointer);
    printf("%ld",ulCharacterCount);

    return 0;
}
// EOF