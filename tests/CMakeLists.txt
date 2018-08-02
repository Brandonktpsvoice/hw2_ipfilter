cmake_minimum_required(VERSION 3.2)

project(tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(TEST_SOURCES test_main.cpp)

add_executable(app_tests ${TEST_SOURCES})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${GTEST_INCLUDE_DIRS} )

target_link_libraries(app_tests prj_lib ${GTEST_LIBRARIES} pthread)

add_test(UnitTests app_tests)
