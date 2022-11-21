cmake_minimum_required(VERSION 3.15)

project(chat_project)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(TEST)
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
elseif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O0")
endif()


# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_subdirectory(Chat)

add_executable(${PROJECT_NAME} ./source/main.cpp)



target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_VEC_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${MATRIX_VEC_LIB_LIBRARIES})



if(TEST)
    message("-----MAIN-----")
    message("Lib link = " ${MATRIX_VEC_LIB_LIBRARIES})
    message("Dir link = " ${MATRIX_VEC_LIB_INCLUDE_DIRS})
    message("---------------")
    enable_testing()
    add_subdirectory(test)
endif()
