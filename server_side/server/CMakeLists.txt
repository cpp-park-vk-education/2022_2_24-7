cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_SERVER_TESTS "Build server test programs" ON)

set(SOURCES "src/server.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
set(${PROJECT_NAME}_lib ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES})
set(server_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${server_include_directories})

if(BUILD_SERVER_TESTS)
    enable_testing()
    add_subdirectory(tests_server)    
endif()

message("server_lib " ${server_lib})
message("server_include_directories " ${server_include_directories})

set(server_lib ${server_lib} PARENT_SCOPE)
set(server_include_directories ${server_include_directories} PARENT_SCOPE)