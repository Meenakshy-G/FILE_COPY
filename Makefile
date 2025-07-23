# Compiler
CC = gcc
CROSS_CC = aarch64-linux-gnu-gcc

# Source files
SRC = $(wildcard *.c listFiles/*.c fileOperation/*.c directoryOperation/*.c)
FILE_NAMES = $(notdir $(SRC))

# Output folders
FOLDERS = release debug

# Object and assembly files
OBJECT  = $(patsubst %.c,release/%.o,$(FILE_NAMES))
DEBUG   = $(patsubst %.c,debug/%.o,$(FILE_NAMES))
ASSEMBLY = $(patsubst %.c,release/%.s,$(FILE_NAMES))

# Options
CFLAGS = -Wall -IlistFiles -IfileOperation -IdirectoryOperation
DEBUG_OPTIONS = -g -c -O0
VPATH = .:listFiles:fileOperation:directoryOperation

# Default target
all : create_folder linux  #rpi
	$(CC) $(CFLAGS) $(OBJECT) -o FILE_LIST_TOOL

# Create output folders
create_folder :
	mkdir -p $(FOLDERS)

# Linux build
linux : create_folder object_files assembly_files debug_files

# Assembly files
assembly_files : create_folder $(ASSEMBLY)
release/%.s : %.c
	$(CC) -S $(CFLAGS) $< -o $@

# Object files
object_files : create_folder $(OBJECT)
release/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

debug_files : create_folder $(DEBUG)
debug/%.o : %.c
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) $< -o $@

# Cross compilation for Raspberry Pi
# rpi : create_folder $(SRC)
# 	$(CROSS_CC) $(CFLAGS) $(SRC) -o release/FILE_LIST_TOOL_for rpi

# Debug executable
debug : debug_files
	$(CC) debug/* -o debug/FILE_LIST_TOOL_DEBUG

# Clean
clean :
	rm -rf $(FOLDERS) FILE_LIST_TOOL