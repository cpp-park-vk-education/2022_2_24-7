cmake_minimum_required(VERSION 3.14)

project(DB)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Router.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Handlers.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Project.cpp"
)

set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Handlers.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IConnection.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IProject.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Project.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IResponse.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/IWorkWithData.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Reply.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Request.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/Router.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/User.hpp")

set(DB_LIB "${PROJECT_NAME}_lib")
set(DB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(DB_LIB ${DB_LIB} PARENT_SCOPE)
set(DB_SOURCES_HEADERS_LIB ${SOURCES} ${HEADERS} PARENT_SCOPE)
set(DB_INCLUDE_DIRS ${DB_INCLUDE_DIRS} PARENT_SCOPE)

add_library(${DB_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${DB_LIB} PUBLIC ${DB_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_DB)    
endif()
