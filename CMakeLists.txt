cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "ci_project")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(project)

message("Project_LIB = ${Project_LIB}")
message("Project_INCLUDE_DIRS = ${Project_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Project_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${Project_INCLUDE_DIRS})