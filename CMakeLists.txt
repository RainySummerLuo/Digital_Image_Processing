cmake_minimum_required(VERSION 3.15)
project(Lab)

set(CMAKE_CXX_STANDARD 14)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\Toolchain\\opencv\\opencv_mingw_build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp lab1.cpp lab1.hpp io.cpp io.h proto.h pgmreader.c)
add_executable(Lab ${SOURCE_FILES})

# linking
target_link_libraries(Lab ${OpenCV_LIBS})