cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Connection.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Serializer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp"
            )
set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/IConnection.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Connection.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/ISerializer.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Serializer.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IServer.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Server.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/ServerConfig.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IRouter.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Request.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Reply.hpp"
            )

set(SERVER_LIB "${PROJECT_NAME}_lib")
set(SERVER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SERVER_LIB ${SERVER_LIB} PARENT_SCOPE)
set(SERVER_SOURCES_HEADERS_LIB ${SOURCES} ${HEADERS} PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS ${SERVER_INCLUDE_DIRS} PARENT_SCOPE)

add_library(${SERVER_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${SERVER_LIB} PUBLIC ${SERVER_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_server)    
endif()
