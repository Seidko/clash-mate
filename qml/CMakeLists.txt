find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Qml WaylandCompositor)
include_directories(${Qt6_INCLUDE_DIRS} ${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Quick_INCLUDE_DIRS})

qt_wrap_cpp(MOC_HEADERS bridge.hpp)

qt_add_library(
    qmlapp
    STATIC
    app.cpp
    viewer.cpp
    bridge.cpp
    ${MOC_HEADERS}
)

target_link_libraries(qmlapp PRIVATE Qt6::WaylandCompositor)
