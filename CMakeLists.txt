
cmake_minimum_required(VERSION 3.5)

project(DecisionModels VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

link_directories(${Eigen_INCLUDE_DIRS})
set (PROJECT_SOURCES
        trunk/core/src/decision_methods/ahp_decision_method.cpp
        trunk/core/src/decision_methods/gm_decision_method.cpp
        trunk/core/src/decision_methods/tropical.cpp
        trunk/core/src/decision_methods/tropical_decision_method.cpp
        trunk/core/src/DecisionModelsDB.cpp
        trunk/core/src/DecisionModel.cpp
        trunk/core/src/main.cpp

        trunk/core/src/ui/StartMenu.cpp
        trunk/core/src/ui/DecisionModelDialog.cpp
        trunk/core/src/ui/CompareCriteriaDialog.cpp
        trunk/core/src/ui/CompareAlternativesDialog.cpp

        trunk/core/src/ui/StartMenu.ui
        trunk/core/src/ui/DecisionModelDialog.ui
        trunk/core/src/ui/CompareCriteriaDialog.ui
        trunk/core/src/ui/CompareAlternativesDialog.ui
)
set (PROJECT_HEADERS
        trunk/core/include/ui/StartMenu.h
        trunk/core/include/ui/DecisionModelDialog.h
        trunk/core/include/ui/CompareCriteriaDialog.h
        trunk/core/include/ui/CompareAlternativesDialog.h

        trunk/core/include/DecisionModel.h
        trunk/core/include/decision_methods/utils.h)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestDm APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets    Eigen3::Eigen)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
        DecisionModelsTests
        trunk/core/src/decision_methods/ahp_decision_method.cpp
        trunk/core/src/decision_methods/gm_decision_method.cpp
        trunk/core/src/decision_methods/tropical.cpp
        trunk/core/src/decision_methods/tropical_decision_method.cpp

        tests/ahp_tasks_tests.cpp
        tests/gm_tasks_tests.cpp
        tests/tropical_tests.cpp
        tests/tropical_tasks_tests.cpp
)


target_link_libraries(DecisionModelsTests gtest_main Eigen3::Eigen)
include(GoogleTest)
gtest_discover_tests(DecisionModelsTests)

