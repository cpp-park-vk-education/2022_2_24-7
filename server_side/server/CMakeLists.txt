cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS "${CMAKE_CURRENT_BINARY_DIR}/include/")
set(SOURCES "${CMAKE_CURRENT_BINARY_DIR}/src/")

set(SERVER_LIB ${PROJECT_NAME}_LIB)
set(SERVER_INCLUDE_DIRS ${HEADERS})

add_library(${SERVER_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${SERVER_LIB} PUBLIC ${HEADERS})

set_target_properties(${SERVER_LIB} PROPERTIES LINKER_LANGUAGE CXX)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests_server)    
endif()

set(SERVER_LIB ${PROJECT_NAME}_LIB PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS "include/" PARENT_SCOPE)