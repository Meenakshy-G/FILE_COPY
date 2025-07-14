# Compilers
CC = gcc
CROSS_CC = aarch64-linux-gnu-gcc

# Source files. 
SRC = $(wildcard *.c fileOperation/*.c)
FILE_NAMES = $(notdir $(SRC))

# Generated files
OBJECT  = $(patsubst %.c,release/%.o,$(FILE_NAMES))
DEBUG   = $(patsubst %.c,debug/%.o,$(FILE_NAMES))
ASSEMBLY = $(patsubst %.c,release/%.s,$(FILE_NAMES))

# Options
CFLAGS = -Wall -fanalyzer -IfileOperation
DEBUG_OPTIONS = -g -c -O0 
FOLDERS = release debug
VPATH = .:fileOperation

# Make all
all : create_folder linux rpi 
	$(CC) $(CFLAGS) $(OBJECT) -o FILECOPY 

# Create folder for output
create_folder :
	mkdir -p $(FOLDERS)

# Make Linux
linux : create_folder object_files assembly_files debug_files

# Make assembly files into release folder
assembly_files : create_folder $(ASSEMBLY)
release/%.s : %.c
	$(CC) -S $(CFLAGS) $< -o $@ 

# Make object files into release folder
object_files : create_folder $(OBJECT)
release/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

# Make object files with debug information into debug folder
debug_files : create_folder $(DEBUG)
debug/%.o : %.c
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) $< -o $@

# Cross compilation for raspberry pi
rpi : create_folder $(SRC)
	$(CROSS_CC) $(CFLAGS) $(SRC) -o release/for_rpi 

# Generate executable with debugging information 
debug : debug_files
	$(CC) debug/* -o debug/FILECOPY_DEBUG 

# Remove all the generated folders
clean : 
	rm -rf $(FOLDERS) FILECOPY