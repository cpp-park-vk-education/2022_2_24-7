cmake_minimum_required(VERSION 3.14)

project(text_editor)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/TextEditor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Command.cpp")

set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/ITextEditor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/TextEditor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Command.hpp")

set(TEXT_EDITOR_LIB "${PROJECT_NAME}_lib")
set(TEXT_EDITOR_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(TEXT_EDITOR_LIB ${TEXT_EDITOR_LIB} PARENT_SCOPE)
set(TEXT_EDITOR_SOURCES_HEADERS_LIB ${SOURCES} ${HEADERS} PARENT_SCOPE)
set(TEXT_EDITOR_INCLUDE_DIRS ${TEXT_EDITOR_INCLUDE_DIRS} PARENT_SCOPE)

add_library(${TEXT_EDITOR_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${TEXT_EDITOR_LIB} PUBLIC ${TEXT_EDITOR_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_text_editor)    
endif()
