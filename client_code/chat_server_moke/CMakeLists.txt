cmake_minimum_required(VERSION 3.16)

project(chat_server_moke VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 protobuf 文件，PB_FILES变量就指代所有的 proto 文件，proto文件就是chat_client项目中的文件
file(GLOB PB_FILES "../chat_client/proto/*.proto")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# 引入模块
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Protobuf HttpServer WebSockets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chat_server_moke
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        httpserver.h httpserver.cpp


    )

# 编译 chat_server_moke 依赖 PROTO_FILES, 具体就是 PB_FILES 变量的值
qt_add_protobuf(chat_server_moke PROTO_FILES ${PB_FILES})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET chat_server_moke APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(chat_server_moke SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(chat_server_moke
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 这里表示需要链接的动态库，加上protobuf，websocket,httpserver
target_link_libraries(chat_server_moke PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Protobuf Qt6::HttpServer Qt6::WebSockets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.chat_server_moke)
endif()
set_target_properties(chat_server_moke PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS chat_server_moke
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chat_server_moke)
endif()
