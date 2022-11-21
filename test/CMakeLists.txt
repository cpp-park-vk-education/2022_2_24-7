cmake_minimum_required(VERSION 3.15)

set(TestName tests)
project(${TestName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

set(SOURCES test.cpp)

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

# GTEST---  
if(TEST)
  message("GTEST_____")
  message("MATRIX_LIB_INCLUDE_DIRS = ${MATRIX_VEC_LIB_INCLUDE_DIRS}")
  message("MATRIX_LIB_LIBRARIES    = ${MATRIX_VEC_LIB_LIBRARIES}")
endif()


add_executable(
    ${TestName}
    ${SOURCES}
)

target_include_directories(${TestName}  PUBLIC  ${MATRIX_VEC_LIB_INCLUDE_DIRS})

target_link_libraries( 
  ${TestName} 
  ${MATRIX_VEC_LIB_LIBRARIES} 
  GTest::gtest_main
)



include(GoogleTest)
gtest_discover_tests(${TestName})
