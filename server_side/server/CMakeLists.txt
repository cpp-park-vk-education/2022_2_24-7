cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SOURCES)
aux_source_directory(include HEADERS)

set(SERVER_LIB ${PROJECT_NAME}_LIB)
set(SERVER_INCLUDE_DIRS ${HEADERS})

add_library(${SERVER_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${SERVER_LIB} PUBLIC ${HEADERS})

set(SERVER_LIB ${SERVER_LIB} PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
