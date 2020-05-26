cmake_minimum_required(VERSION 3.15)
project(Lab)

set(CMAKE_CXX_STANDARD 14)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\Toolchain\\opencv\\opencv_mingw_build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp lab1.cpp lab1.hpp io.cpp io.hpp pgmreader.hpp pgmreader.cpp lab2.cpp lab2.hpp lab3.cpp lab3.hpp lab4.cpp lab4.hpp lab5.cpp lab5.hpp lab6.cpp lab6.hpp lab7.cpp lab7.hpp)
add_executable(Lab ${SOURCE_FILES})

# linking
target_link_libraries(Lab ${OpenCV_LIBS})