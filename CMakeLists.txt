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
string(APPEND CMAKE_CXX_FLAGS " -Wlogical-op  -Wduplicated-cond -Wcast-qual -Wcast-align -g")

if(BUILD_DEV)
    string(APPEND CMAKE_CXX_FLAGS " -g -O0")
endif()

if(BUILD_SANITIZE)
    string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif()

if(BUILD_VALGRIND)
    
endif()

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
    
    message("Server LIB " ${SERVER_SIDE_LIB})
    message("Server DIR " ${SERVER_SIDE_INCLUDE_DIRECTORIES})
    
    set(${PROJECT_NAME}_lib ${SERVER_SIDE_LIB} ${CLIENT_SIDE_LIB})
    set(${PROJECT_NAME}_include_directories ${SERVER_SIDE_INCLUDE_DIRECTORIES} ${CLIENT_SIDE_INCLUDE_DIRS})

    message("mutual_editing_lib " ${MUTUAL_EDITING_LIB})
    message("mutual_editing_include_directories " ${mutual_editing_include_directories})

    enable_testing()
    
    add_test(tests_text_editor "./server_side/text_editor/tests_text_editor/testsForTextEditor")
    add_test(tests_server "./server_side/server/tests_server/testsForServer")
    add_test(tests_DB "./server_side/DB/tests_DB/testsForDB")
    add_test(tests_client_side "./client_side/tests_client_side/testsForClientSide")

    add_subdirectory(tests)
endif()
