cmake_minimum_required(VERSION 3.14)

project(testsForDB)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "tests.cpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${DB_LIB} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${DB_INCLUDE_DIRS})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
