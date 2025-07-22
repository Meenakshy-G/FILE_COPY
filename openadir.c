#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "common.h"

int main (int argc, char *argv[])
{
    char *pcDirectory;
    DIR *pstDirectoryPointer = NULL;
    struct dirent *pstDirectoryDetails = NULL;

    if (INPUT_ARGUMENTS == argc)
    {
        pcDirectory = argv[1];

        if (NULL != pcDirectory)
        {  
            pstDirectoryPointer = opendir("testdirectory/dirinsidedir");

            while (NULL != (pstDirectoryDetails = readdir(pstDirectoryPointer)))
            {
                if (pstDirectoryDetails->d_type == 8)
                {
                    printf("NAME: %s \n", pstDirectoryDetails->d_name);
                    printf("id: %ld \n", pstDirectoryDetails->d_ino);
                    printf("type: %d \n\n", pstDirectoryDetails->d_type);
                }
            }



            closedir(pstDirectoryPointer); 
        }
    }

    return 0;
}