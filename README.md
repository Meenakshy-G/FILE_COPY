## **FILE_COPY**

Project to create the copy of a given input file. The copy of the file is created within the same folder, renamed into 'file'_copy.'extension'. Input can be any file or path. 

**Features**

* source code organised in multiple directories.
* separate release and debug builds.

## Building with make 

$ make all

Output: FILECOPY

$ make clean 

Output: Removes all the generated files and directories.

$ make linux

Output: All the assembly files and object files created in release folder

$make debug 

Output: All the object files with debug information created in the debug folder.
