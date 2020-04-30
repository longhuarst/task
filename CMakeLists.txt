cmake_minimum_required(VERSION 3.16)
project(task C)


file(GLOB SOURCES
        Logger.h						//*号对应具体的文件名
        Logger.c
        *.h
        *.c
        )


set(CMAKE_C_STANDARD 99)

add_executable(task main.c ${SOURCE_FILES} ${SOURCES})

