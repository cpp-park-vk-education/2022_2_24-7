cmake_minimum_required(VERSION 3.14)

project(testsForServer)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "tests.cpp")

find_package(GTest REQUIRED)

if(GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SERVER_LIB} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${SERVER_INCLUDE_DIRS})

gtest_discover_tests(${PROJECT_NAME})
