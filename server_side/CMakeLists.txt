cmake_minimum_required(VERSION 3.14)

project(server_side)

set(CMAKE_CXX_STANDARD 17)

set(CHAT_LIB ${CHAT_LIB} PARENT_SCOPE)
set(CHAT_INCLUDE_DIRS ${CHAT_INCLUDE_DIRS} PARENT_SCOPE)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CHAT_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${CHAT_INCLUDE_DIRS})