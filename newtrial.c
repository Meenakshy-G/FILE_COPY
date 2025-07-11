#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include "common.h"

int main(uint16 argc, char *argv[])
{
    FILE *pstFilePointer            = NULL;
    FILE *pstDestinationFilePointer = NULL;
    uint8 *pucInputFileName         = NULL;
    uint8 *pucOutputFileName        = NULL;
    uint8 *pucOutputFile        = NULL;

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
    
    pucOutputFile = basename(pucInputFileName);
    pucOutputFileName = strcat(pucOutputFile,"_copy");
    pstDestinationFilePointer = fopen(pucOutputFileName,"w+");

    if(pstDestinationFilePointer == NULL)
    {
        printf("Error opening the file");
        fclose(pstDestinationFilePointer);
    }

    return 0;
}