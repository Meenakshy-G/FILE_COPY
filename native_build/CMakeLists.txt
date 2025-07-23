cmake_minimum_required(VERSION 3.10)
project(CROSS C)

include_directories(${CMAKE_SOURCE_DIR}/fileOperation 
                    ${CMAKE_SOURCE_DIR}/directoryOperation 
                    ${CMAKE_SOURCE_DIR}/listFiles)

add_executable(FILE_LIST_TOOL ${CMAKE_SOURCE_DIR}/../main.c
                            ${CMAKE_SOURCE_DIR}/../fileOperation/fileOperation.c
                            ${CMAKE_SOURCE_DIR}/../directoryOperation/directoryOperation.c
                            ${CMAKE_SOURCE_DIR}/../listFiles/listFiles.c)

target_compile_options(FILE_LIST_TOOL PRIVATE -fanalyzer)