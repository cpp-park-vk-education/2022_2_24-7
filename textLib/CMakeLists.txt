cmake_minimum_required(VERSION 3.14)

project(textEditor)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES lineElement.cpp lineOfText.cpp textEditor.cpp)
set(HEADERS include/lineElement.hpp include/lineOfText.hpp include/textEditor.hpp)


# set(TEXT_LIB ${TEXT_LIB} PARENT_SCOPE)
# set(TEXT_INCLUDE_DIRS . PARENT_SCOPE)

set(LIB_NAME ${PROJECT_NAME}_LIB)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC "../textLib/include")

set(TEXT_LIB ${LIB_NAME} PARENT_SCOPE)
set(TEXT_INCLUDE_DIRS ${LIB_NAME} ./include PARENT_SCOPE)

# set(TEXT_LIB ${Project_LIB})
# set(TEXT_INCLUDE_DIRS ${Project_INCLUDE_DIRS})
