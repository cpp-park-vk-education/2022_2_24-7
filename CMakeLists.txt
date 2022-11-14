cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "joint_viewing")

set(TestDirecotries "tests")
set(Directories "libs" "server" "client")
set(Executables "client/src/main.cpp")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
message(${Directories})
add_subdirectory(${Directories})

add_executable(${PROJECT_NAME} ${Executables})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Project_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${Project_INCLUDE_DIRS})

enable_testing()
add_subdirectory(${TestDirecotries})
