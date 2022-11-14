cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "Libraries")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(Libs "examplelib")

add_subdirectory(${Libs})

set(Project_LIB ${Project_LIB} PARENT_SCOPE)
set(Project_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)
