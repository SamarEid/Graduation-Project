cmake_minimum_required(VERSION 3.5)

project(Infotainment_System VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(spdlog REQUIRED)

set(PROJECT_SOURCES
        Communication/Communication.h
        Communication/Communication.cpp
        UI/Start/startwindow.h
        UI/Start/startwindow.cpp
        UI/Start/startwindow.ui
        ADAS/ADAS_Notification.h
        ADAS/ADAS_Notification.cpp
        UI/assets/Icons.qrc
        UI/assets/TrafficSigns.qrc
        main.cpp
        UI/MainWindow/mainwindow.cpp
        UI/MainWindow/mainwindow.h
        UI/MainWindow/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Infotainment_System
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Infotainment_System APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Infotainment_System SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Infotainment_System
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Infotainment_System PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PahoMqttCpp::paho-mqttpp3 spdlog::spdlog)

set_target_properties(Infotainment_System PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Infotainment_System)
endif()
