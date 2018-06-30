cmake_minimum_required(VERSION 3.2)

project(project_lib)

add_library(prj_lib lib.cpp)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
