cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SOURCES)
aux_source_directory(include HEADERS)

set(SERVER_LIB ${PROJECT_NAME}_LIB)
set(SERVER_INCLUDE_DIRS ${HEADERS})

add_library(${SERVER_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${SERVER_LIB} PUBLIC ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${SERVER_INCLUDE_DIRS})

set(FOR_TEST_LIB ${SERVER_LIB})
set(FOR_TEST_INCLUDE_DIRS ${SERVER_INCLUDE_DIRS})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests_server)    
endif()
