cmake_minimum_required(VERSION 3.15)

project(textEditor)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES_TEXT "lineElement.cpp" "lineOfText.cpp" "textEditor.cpp" PARENT_SCOPE)
set(SOURCES_TEXT "lineElement.cpp" "lineOfText.cpp" "textEditor.cpp")



set(LIB_NAME ${PROJECT_NAME}_LIB)

set(TEXT_LIB ${LIB_NAME} PARENT_SCOPE)
set(TEXT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

set(TEXT_LIB ${LIB_NAME})
set(TEXT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} )

add_library(${LIB_NAME} ${SOURCES_TEXT})

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "../textLib/")
