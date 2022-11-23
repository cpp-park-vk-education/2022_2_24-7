cmake_minimum_required(VERSION 3.14)

project(server_side)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(server)
set(SERVER_SIDE_LIB ${SERVER_LIB})
set(SERVER_SIDE_INCLUDE_DIRS ${SERVER_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${SERVER_SIDE_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${SERVER_INCLUDE_DIRS})

set(SERVER_SIDE_LIB ${SERVER_LIB} PARENT_SCOPE)
set(SERVER_SIDE_INCLUDE_DIRS "server/${SERVER_INCLUDE_DIRS}" PARENT_SCOPE)
