cmake_minimum_required(VERSION 3.14)

project(server_side)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(server)
add_subdirectory(text_editor)
# add_subdirectory(chat)

add_library(${PROJECT_NAME}_lib STATIC ${server_lib})
set(${PROJECT_NAME}_lib ${server_lib})
set(${PROJECT_NAME}_include_directories ${server_include_directories})

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${server_side_include_directories})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} ${server_side_lib})
target_include_directories(${PROJECT_NAME} PUBLIC ${server_side_include_directories})

message("server_side_lib " ${server_side_lib})
message("server_side_include_directories " ${server_side_include_directories})

set(${PROJECT_NAME}_lib ${server_side_lib} PARENT_SCOPE)
set(${PROJECT_NAME}_include_directories ${server_side_include_directories} PARENT_SCOPE)
