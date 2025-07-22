//****************************** directoryOperation ****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// Summary : Contains all forward declarations required for directory operations 
//           inside listFiles.c file.
// Note    : None.
//******************************************************************************
#ifndef _DIRECTORY_OPERATION_H
#define _DIRECTORY_OPERATION_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "../common.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool directoryOperationOpen(DIR **pstDirectory, char **pcPath,
                            struct dirent **pstContents);
bool directoryOperationClose(DIR **pstDirectory);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _DIRECTORY_OPERATION_H
// EOF