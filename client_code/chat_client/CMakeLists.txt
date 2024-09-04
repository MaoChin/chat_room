# cmake的最小依赖版本
cmake_minimum_required(VERSION 3.16)

project(chat_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 protobuf 文件，PB_FILES变量就指代所有的 proto 文件
file(GLOB PB_FILES "./proto/*.proto")

# 引入各种组件
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# 这里引入 protobuf
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Protobuf)

set(PROJECT_SOURCES
        main.cpp
        mainwidget.cpp
        mainwidget.h
        mainwidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # 指定编译时的依赖程序
    qt_add_executable(chat_client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        model/data.h
        resource.qrc
        middlewindowarea.h middlewindowarea.cpp
        debug.h
        rightwindowmessageshowarea.h rightwindowmessageshowarea.cpp
        rightwindowmessageeditarea.h rightwindowmessageeditarea.cpp
        selfinfowidget.h selfinfowidget.cpp
        userinfowidget.h userinfowidget.cpp
        sessiondetailwidget.h sessiondetailwidget.cpp
        groupchoosefrienddialog.h groupchoosefrienddialog.cpp
        groupsessiondetailwidget.h groupsessiondetailwidget.cpp
        addfrineddialog.h addfrineddialog.cpp
        historymessagedialog.h historymessagedialog.cpp
        usernameloginwidget.h usernameloginwidget.cpp
        phoneloginwidget.h phoneloginwidget.cpp
        toast.h toast.cpp
    )
    # 编译 chat_client 依赖 PROTO_FILES, 具体就是 PB_FILES 变量的值
    qt_add_protobuf(chat_client PROTO_FILES ${PB_FILES})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET chat_client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(chat_client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(chat_client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(chat_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.chat_client)
endif()
set_target_properties(chat_client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS chat_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chat_client)
endif()
