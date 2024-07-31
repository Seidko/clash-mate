set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.20)

include(cmake/golang.cmake)

project(clash-mate VERSION 0.0.1 LANGUAGES C CXX Go)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Qml)

include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Quick_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ".")

list(APPEND CMAKE_GO_FLAGS "-ldflags \"-s -w\"")

link_directories(. ${CMAKE_CURRENT_BINARY_DIR})
add_go_library(clash STATIC main.go)
qt_add_executable(clash-mate src/main.cpp)

set_property(TARGET clash-mate PROPERTY CXX_STANDARD 23)
set(CGO_ENABLED 1)

add_dependencies(clash-mate clash)
target_link_libraries(clash-mate PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Widgets libclash.a)
