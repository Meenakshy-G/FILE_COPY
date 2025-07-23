//**************************** FileOperations **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// Summary : Contains all global constants and forward declarations required for 
//           fileOperation.c file functions. 
// Note    : None
//******************************************************************************
#ifndef _FILE_OPERATION_H
#define _FILE_OPERATION_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "../common.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define EXTENSION_SEPARATION ('.')
#define READ ("rb")
#define WRITE ("wb")

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool fileOperationOpen(FILE **pstFile, char *pstFileName, char *pstMode);
bool fileOperationSize(FILE *pstFile, uint32 *pulFileSize);
bool fileOperationClose(FILE *pstFile);
bool fileOperationFindExtension(char *pcFileName, char **ppcExtension,
                                bool *pblExtensionStatus);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _FILE_OPERATION_H 
// EOF 