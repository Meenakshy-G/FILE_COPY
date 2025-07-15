//**************************** FileCopy ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// Summary : Contains all type definitions and forward declarations.
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

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool fileCopyTool(char *pcFileName, char *pcFileNameDuplicate);

//*********************** Inline Method Implementations ************************

//******************************************************************************

#endif // _FILE_COPY_H 
// EOF 