cmake_minimum_required(VERSION 3.14)

project(testsForTextEditor)

set(SOURCES "tests.cpp")

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(GTest CONFIG)
# if(NOT Gtest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
# endif(NOT Gtest_FOUND)

include(GoogleTest)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Project_LIB} GTest::gtest_main ${FOR_TEST_LIB})
target_include_directories(${PROJECT_NAME} PRIVATE ${FOR_TEST_INCLUDE_DIRS})

gtest_discover_tests(${PROJECT_NAME})
