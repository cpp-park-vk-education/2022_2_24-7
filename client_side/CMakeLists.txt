cmake_minimum_required(VERSION 3.14)

project(client_side)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES /src/main.cpp)
set(HEADERS /include/main.hpp)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)    
endif()

