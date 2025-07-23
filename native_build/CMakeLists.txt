cmake_minimum_required(VERSION 3.10)
project(CROSS C)

include_directories(${CMAKE_SOURCE_DIR}/../fileOperation 
                    ${CMAKE_SOURCE_DIR}/../fileCopy)

# For cross-compilation to Raspberry pi.
add_executable(FILECOPYTOOL ${CMAKE_SOURCE_DIR}/../main.c
                            ${CMAKE_SOURCE_DIR}/../fileOperation/fileOperation.c
                            ${CMAKE_SOURCE_DIR}/../fileCopy/fileCopy.c)

target_compile_options(FILECOPYTOOL PRIVATE -fanalyzer)