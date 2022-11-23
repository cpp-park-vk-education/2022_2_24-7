cmake_minimum_required(VERSION 3.14)

project(text_editor)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FOR_TEST_LIB "${PROJECT_NAME}_LIB")
set(FOR_TEST_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include")

set(SOURCES src/line.cpp)
set(HEADERS include/line.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${FOR_TEST_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${FOR_TEST_INCLUDE_DIRS})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests_text_editor)    
endif()
