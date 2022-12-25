cmake_minimum_required(VERSION 3.14)

project(_text_editor)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/TextEditor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Command.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SearcherForPlace.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TranslatorFromList.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/WorkWithData.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/WorkWithLogFile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/WorkWithCppFile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Functors.cpp"
    )

set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/SearcherForPlace.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/TextEditor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/TranslatorFromList.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WorkWithData.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WorkWithFile.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WorkWithLogFile.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Functors.hpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/Answer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/Command.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/element.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/ISearchForPlace.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/ITextEditor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/ITranslator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/IWorkWithData.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/IWorkWithFile.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/StartOfLine.hpp"
    )

set(TEXT_EDITOR_LIB "${PROJECT_NAME}_lib")
set(TEXT_EDITOR_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/interfaces")

set(TEXT_EDITOR_LIB ${TEXT_EDITOR_LIB} PARENT_SCOPE)
set(TEXT_EDITOR_SOURCES_HEADERS_LIB ${SOURCES} ${HEADERS} PARENT_SCOPE)
set(TEXT_EDITOR_INCLUDE_DIRS ${TEXT_EDITOR_INCLUDE_DIRS} PARENT_SCOPE)

add_library(${TEXT_EDITOR_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${TEXT_EDITOR_LIB} PUBLIC ${TEXT_EDITOR_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_text_editor)
endif()
