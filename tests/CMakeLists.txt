cmake_minimum_required(VERSION 3.15)

project(tests)

# set(TestSOURCES "testExampleLib/tests.cpp" "editorTests/textEditor.cpp" "editorTests/lineOfText.cpp" "editorTests/lineElement.cpp")
set(TestSOURCES "editorTests/textEditor1.cpp" "editorTests/lineOfText1.cpp" "editorTests/lineElement1.cpp")
set(OUR_LIBS ${TEXT_LIB})
set(OUR_DIRS ${TEXT_INCLUDE_DIRS})

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

target_include_directories(${PROJECT_NAME} PUBLIC ${OUR_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TEST_LIB} ${OUR_LIBS} GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
