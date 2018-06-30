cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wpedantic -Wall -Wextra" ${CMAKE_CXX_FLAGS})

configure_file(version.h.in version.h)

set(SOURCES src/main.cpp)

add_executable(ip_filter ${SOURCES})

add_subdirectory(lib)
include_directories(lib)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

target_link_libraries(ip_filter prj_lib)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    install(TARGETS ip_filter RUNTIME DESTINATION bin)
else()
    install(TARGETS ip_filter RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)
endif()

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT email@example.com)

include (CPack)

########
# unit testing
########

enable_testing()
add_subdirectory(tests)
