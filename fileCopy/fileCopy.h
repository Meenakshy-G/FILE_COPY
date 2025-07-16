//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// Summary : Contains all global constants and forward declarations 
//           required for fileCopy.c file functions.
// Note    : None
//******************************************************************************
#ifndef _FILE_COPY_H
#define _FILE_COPY_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "../common.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define FOLDER_SEPARATION ('/')
#define EXTENSION_SEPARATION ('.')
#define MODIFIER ("_copy")
#define READ_MODE ("rb")
#define WRITE_MODE ("wb")

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool fileCopyTool(char *pcFileName);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _FILE_COPY_H 
// EOF 