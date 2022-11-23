cmake_minimum_required(VERSION 3.14)

project(mutual_editing)

option(BUILD_ALL "Build all directories and tests" ON)
OPTION(BUILD_SERVER_SIDE "Build server" OFF)
OPTION(BUILD_CLIENT_SIDE "Build client" OFF)
option(BUILD_TESTS "Build global test programs" OFF)
OPTION(BUILD_DEV  "Development build" OFF)
OPTION(BUILD_VALGRIND "Memory testing" OFF)
OPTION(BUILD_SANITIZE "Sanitize" OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion -fprofile-arcs")
string(APPEND CMAKE_CXX_FLAGS " -Wlogical-op  -Wduplicated-cond -Wcast-qual -Wcast-align")

if(BUILD_SERVER_SIDE OR BUILD_ALL)
    message("BUILD SERVER SIDE")
    add_subdirectory(server_side)
    
endif()

if(BUILD_CLIENT_SIDE OR BUILD_ALL)
    message("BUILD CLIENT SIDE")
    add_subdirectory(client_side)
endif()

if(BUILD_TESTS OR BUILD_ALL)
    message("BUILD GLOBAL TESTS")
    enable_testing()
    
    message("Server LIB " ${SERVER_SIDE_LIB})
    message("Server DIR " ${SERVER_SIDE_INCLUDE_DIRS})
    
    set(PROJECT_LIB ${SERVER_SIDE_LIB})
    set(PROJECT_INCLUDE_DIRECTORIES "../server_side/${SERVER_SIDE_INCLUDE_DIRS}")
    add_subdirectory(tests)
endif()

if(BUILD_DEV)
    string(APPEND CMAKE_CXX_FLAGS " -g -O0")
endif()

if(BUILD_SANITIZE)
    string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif()

if(BUILD_VALGRIND)
    
endif()
