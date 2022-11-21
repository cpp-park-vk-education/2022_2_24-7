cmake_minimum_required(VERSION 3.15)
project(Vector_Matrix)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TEST)
    message("WALL MATR")
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
endif()

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/chat.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/chat.hpp)

# ??????????
file(GLOB HEADER_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(TEST)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0 -g")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
elseif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3")
endif()


file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_DIRS})


# set(MATRIX_VEC_LIB_LIBRARIES       ${PROJECT_NAME}                 )
# set(MATRIX_VEC_LIB_INCLUDE_DIRS    ${HEADER_DIRS}                 )
# Выше
# set(MATRIX_VEC_LIB_LIBRARIES       ${PROJECT_NAME}     PARENT_SCOPE)
# set(MATRIX_VEC_LIB_INCLUDE_DIRS    ${HEADER_DIRS}     PARENT_SCOPE)

# set(MATRIX_VEC_LIB_LIBRARIES       ${PROJECT_NAME}                 )
# set(MATRIX_VEC_LIB_INCLUDE_DIRS    ${INCLUDE_DIRS}                 )
set(MATRIX_VEC_LIB_LIBRARIES       ${PROJECT_NAME}     PARENT_SCOPE)
set(MATRIX_VEC_LIB_INCLUDE_DIRS    ${INCLUDE_DIRS}     PARENT_SCOPE)
