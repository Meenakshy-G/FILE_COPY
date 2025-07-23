cmake_minimum_required(VERSION 3.10)
project(FILE_COPY C)
include(ExternalProject)
ExternalProject_Add(RELEASE
SOURCE_DIR ${CMAKE_SOURCE_DIR}/native_build
BINARY_DIR ${CMAKE_BINARY_DIR}/Release_folder
CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
INSTALL_COMMAND ""
)
ExternalProject_Add(DEBUG
SOURCE_DIR ${CMAKE_SOURCE_DIR}/native_build
BINARY_DIR ${CMAKE_BINARY_DIR}/Debug_folder
CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug
INSTALL_COMMAND ""
)
ExternalProject_Add(RELEASE_RPI
SOURCE_DIR ${CMAKE_SOURCE_DIR}/cross_build
BINARY_DIR ${CMAKE_BINARY_DIR}/Release_rpi_folder
CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc 
INSTALL_COMMAND ""
)


# The directories to look for header files are added.
include_directories(${CMAKE_SOURCE_DIR}/fileOperation 
                    ${CMAKE_SOURCE_DIR}/fileCopy)

# The normal executable.
add_executable(FILECOPYTOOL ${CMAKE_SOURCE_DIR}/main.c
                            ${CMAKE_SOURCE_DIR}/fileOperation/fileOperation.c
                            ${CMAKE_SOURCE_DIR}/fileCopy/fileCopy.c)

set_target_properties(FILECOPYTOOL PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
                       "${CMAKE_SOURCE_DIR}")

target_compile_options(FILECOPYTOOL PRIVATE -fanalyzer)

