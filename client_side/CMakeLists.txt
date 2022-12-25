cmake_minimum_required(VERSION 3.14)
project(client VERSION 0.1 LANGUAGES CXX)


add_subdirectory(text_editor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Если не заработает boost, то укажи данную переменную с путём до boost # set(Boost_INCLUDE_DIR "C:/boost_1_81_0")
find_package(Boost 1.80.0 COMPONENTS serialization system thread)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)


set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Client.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h"
)

set(GUI "${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.ui")

set(CLIENT_SIDE_LIB "${PROJECT_NAME}_lib")
set(CLIENT_SIDE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")


qt_add_executable(client
    MANUAL_FINALIZATION
    ${SOURCES}
    ${HEADERS}
    ${GUI}
)


target_link_libraries(client PRIVATE Qt6::Widgets)
target_link_libraries(client PRIVATE Qt6::Network)
target_link_libraries(client PRIVATE Qt6::Core Qt6::Gui)

target_link_libraries(client PRIVATE ${TEXT_EDITOR_LIB})
target_link_libraries(client PRIVATE ${Boost_LIBRARIES})
target_link_libraries(client PUBLIC ${SOURCES})

target_include_directories(client PUBLIC ${CLIENT_SIDE_INCLUDE_DIRS})
target_include_directories(client PRIVATE ${TEXT_EDITOR_INCLUDE_DIRS})


install(TARGETS client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(client)


if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_client_side)
endif()
