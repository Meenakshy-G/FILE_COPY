//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// Summary : Contains all type definitions and forward declarations.
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
#define SIZE (1)

//***************************** Global Variables ******************************* 

//**************************** Forward Declarations **************************** 
bool FileOperationOpenFile(FILE **pstFile, 
                           const char *pstFileName, const char *pstMode);
bool FileOperationCopyContent(uint32 *pulFileSize, FILE *pstFile, 
                              FILE *pstCopyFile );
bool FileOperationFileSize(FILE *pstFile, uint32 *pulFileSize);
bool FileOperationCloseFile(FILE *pstFile);
//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _FILE_OPERATION_H 
// EOF 