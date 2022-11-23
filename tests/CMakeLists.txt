cmake_minimum_required(VERSION 3.14)

project(tests)

set(CMAKE_CXX_STANDARD 17)

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

set(TEST_SOURCES "testExampleLib/tests.cpp")
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main) 
gtest_discover_tests(${PROJECT_NAME})
