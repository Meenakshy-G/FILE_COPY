//**************************** FileOperation ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// Summary : Contains global constants and forward declarations.
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
bool fileOperationOpen(FILE **pstFile, int8 *pcFileName, int8 *pstMode);
bool fileOperationSize(FILE *pstFile, uint32 *pulFileSize);
bool fileOperationClose(FILE *pstFile);
bool fileOperationFindExtension(int8 *pcFileName, int8 **ppcExtension,
                                bool *pblExtensionStatus);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _FILE_OPERATION_H 
// EOF 