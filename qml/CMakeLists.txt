find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Qml)

qt_add_library(
    qmlapp
    STATIC
    app.cpp
    viewer.cpp
)

include_directories(${Qt6_INCLUDE_DIRS} ${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Quick_INCLUDE_DIRS})
# target_link_libraries(qmlapp Qt6::Qml Qt6::Quick Qt6::Core Qt6::Gui Qt6::Widgets)