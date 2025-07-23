//****************************** directoryOperation ****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// Summary : Contains forward declarations required for directory operations.
// Note    : None.
//******************************************************************************
#ifndef _DIRECTORY_OPERATION_H
#define _DIRECTORY_OPERATION_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include "../common.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool directoryOperationOpen(DIR **ppstDirectory, char **ppcPath);
bool directoryOperationClose(DIR **ppstDirectory);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _DIRECTORY_OPERATION_H
// EOF