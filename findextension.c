#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "fileOperation.h"

int main (int argc, char *argv[])
{
    char *pcInputFileName = NULL;
    char *pcExtension = NULL;
    bool blExtensionStatus = false;

    if (INPUT_ARGUMENTS == argc)
    {
        pcInputFileName = argv[1];

        if (NULL != pcInputFileName)
        {
           if (true == fileOperationFindExtension(pcInputFileName, 
                                                   &pcExtension, 
                                                   &blExtensionStatus))
            {
                if (true == blExtensionStatus)                                     //TODO: somthing wrong here
                {
                    printf("Extension is: %s\n", pcExtension);
                }
                else
                {
                    printf("No Extension for current file: Type Unknown\n");
                }
                
            }
            else
            {
                printf("Cannot Find Extension\n");
            }
        }
    }

    return 0;
}