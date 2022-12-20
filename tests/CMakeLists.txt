cmake_minimum_required(VERSION 3.14)

project(tests)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES "testExampleLib/tests.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${mutual_editing_lib} GTest::gtest_main GTest::gmock)
target_include_directories(${PROJECT_NAME} PUBLIC ${mutual_editing_include_directories})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
