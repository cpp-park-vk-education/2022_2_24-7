cmake_minimum_required(VERSION 3.14)

project(tests)
set(TestSOURCES "testExampleLib/tests.cpp")

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(${PROJECT_NAME} ${TestSOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Project_LIB} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${Project_INCLUDE_DIRS})

gtest_discover_tests(${PROJECT_NAME})