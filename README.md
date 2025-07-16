## **FILE_COPY**

Project to create the copy of a given input file. The copy of the file is 
created within the same folder, renamed into 'file'_copy.'extension'. 
Input can be any file within source directory or path to the file. 

**Features**

* source code organised in multiple directories.
* separate native and cross-compile builds.
* makefile and cmake files given.

## Building with make 

$ make all

Output: FILECOPYTOOL

$ make clean 

Output: Removes all the generated files and directories.

$ make linux

Output: All the assembly files and object files created in release folder

$make debug 

Output: All the object files with debug information created in the debug folder.

## Building with cmake 

$ cmake -S. -B Build && cmake --build Build

Ouput : FILECOPYTOOL 
        generated within current source directory and all other 
        remaining release and debug folders created inside Build directory.

## To Run Executable

$ ./FILECOPYTOOL "filename or path"