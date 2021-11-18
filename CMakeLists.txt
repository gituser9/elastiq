cmake_minimum_required(VERSION 3.5)

project(elastiq VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Network Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Widgets LinguistTools REQUIRED)

set(TS_FILES elastiq_ru_RU.ts)
#set(CUR_TARGET elastiq)

file(GLOB PROJECT_SOURCES
        *.cpp
        *.h
        *.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(elastiq
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET elastiq APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(elastiq SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        if (APPLE)
            set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
            set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.elastiq")
            set(MACOSX_BUNDLE_INFO_STRING "A cross-platform ElasticSearch GUI client")
#            set(MACOSX_BUNDLE_ICON_FILE "shadowsocks-qt5.icns")
            set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
            set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
            set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
#            add_executable(${APP_NAME} MACOSX_BUNDLE ${SOURCE}
#                    "icons/shadowsocks-qt5.icns")
            add_executable(elastiq MACOSX_BUNDLE ${PROJECT_SOURCES})
        else()
            add_executable(elastiq ${PROJECT_SOURCES})
        endif()
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(elastiq PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(elastiq)
endif()
