cmake_minimum_required(VERSION 3.16)

project(DriverSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 包含头文件路径，这样代码里的 #include "xxx.h" 就不需要改
include_directories(Models Controllers Views)

set(PROJECT_SOURCES
        main.cpp
        Views/mainwindow.cpp
        Views/mainwindow.h
        Views/mainwindow.ui
        Models/QuestionManager.cpp
        Models/QuestionManager.h
        Models/ScoreManager.cpp
        Models/ScoreManager.h
        Models/GlobalTypes.h
        Controllers/ExamController.cpp
        Controllers/ExamController.h
        Controllers/AdminController.cpp
        Controllers/AdminController.h
        Controllers/ScoreController.cpp
        Controllers/ScoreController.h
        Controllers/ReviewController.cpp
        Controllers/ReviewController.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DriverSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DriverSystem APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DriverSystem SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DriverSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DriverSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DriverSystem)
endif()
set_target_properties(DriverSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DriverSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DriverSystem)
endif()

# 自动复制资源文件到构建目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/questions.txt
          ${CMAKE_CURRENT_SOURCE_DIR}/scores.txt   # 把这个也加进去
     DESTINATION ${CMAKE_BINARY_DIR})
