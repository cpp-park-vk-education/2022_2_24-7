cmake_minimum_required(VERSION 3.10)

project("Project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")

set(LIB_NAME project)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(Project_LIB ${LIB_NAME})
set(Project_LIB ${Project_LIB} PARENT_SCOPE)
set(Project_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(Project_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)

message("Project_LIB = ${Project_LIB}")
message("Project_INCLUDE_DIRS = ${Project_INCLUDE_DIRS}")

enable_testing()
add_subdirectory(tests)