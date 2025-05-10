cmake_minimum_required(VERSION 3.10.0)
project(SigGen VERSION 0.1.0 LANGUAGES C)

add_executable(SigGen main.c serial.c DG4202.c)

include_directories("C:/Program Files/IVI Foundation/VISA/Win64/Include")

target_link_libraries(SigGen PRIVATE "C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa64.lib")
target_link_libraries(SigGen PRIVATE "C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa32.lib")
target_link_libraries(SigGen PRIVATE "C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/nivisa64.lib")