## **List Files**

Project to list all the files in a given directory, if provided with the path 
to the directory, using linked list.
The list contains the name of the file , file type and file size.

**Features**

* source code organised in multiple directories.
* makefile and cmake files given.

## Building with make 

$ make all

Output: FILE_LIST_TOOL

$ make clean 

Output: Removes all the generated files and directories.

$ make linux

Output: All the assembly files and object files created in release folder

$make debug 

Output: All the object files with debug information created in the debug folder.

## Building with cmake 

$ cmake -S. -B Build && cmake --build Build

Ouput : FILE_LIST_TOOL \
        generated within current source directory and all other 
        remaining release and debug folders created inside Build directory.

## To Run Executable

$ ./FILE_LIST_TOOL "path to directory"