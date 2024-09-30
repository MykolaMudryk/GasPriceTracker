cmake_minimum_required(VERSION 3.16)

project(GasPriceTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Gui Network WebSockets)

qt_standard_project_setup()

qt_add_executable(appGasPriceTracker
    main.cpp
)

qt_add_qml_module(appGasPriceTracker
    URI GasPriceTracker
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        GasPriceClient.h
        GasPriceClient.cpp
    RESOURCES
        qml.qrc
)

set_target_properties(appGasPriceTracker PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appGasPriceTracker
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appGasPriceTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
