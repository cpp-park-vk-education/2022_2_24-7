cmake_minimum_required(VERSION 3.14)

project(tests)

set(TestSOURCES "testExampleLib/tests.cpp" "editorTests/textEditor.cpp" "editorTests/lineOfText.cpp" "editorTests/lineElement.cpp")

set(CMAKE_CXX_STANDARD 17)
set(TEXT_LIB ${Project_LIB} PARENT_SCOPE)
set(TEXT_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)

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

include(GoogleTest)

add_executable(${PROJECT_NAME} ${TestSOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TEST_LIB} GTest::gtest_main ${TEXT_LIB})

gtest_discover_tests(${PROJECT_NAME})
