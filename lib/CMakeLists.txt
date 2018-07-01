cmake_minimum_required(VERSION 3.2)

project(project_lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(prj_lib lib.cpp)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
