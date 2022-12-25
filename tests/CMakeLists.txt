cmake_minimum_required(VERSION 3.14)

project(tests)

# set(TestSOURCES "testExampleLib/tests.cpp" "editorTests/textEditor.cpp" "editorTests/lineOfText.cpp" "editorTests/lineElement.cpp")
set(TestSOURCES "testExampleLib/tests.cpp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GTEST
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${TestSOURCES})

target_link_libraries(${PROJECT_NAME} ${mutual_editing_lib} GTest::gtest_main GTest::gmock)
target_include_directories(${PROJECT_NAME} PUBLIC ${mutual_editing_include_directories})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
