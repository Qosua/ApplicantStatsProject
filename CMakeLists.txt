cmake_minimum_required(VERSION 4.1)
project(ApplicantStatsProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (DEFINED ENV{QT_ROOT})
    set(QT_ROOT_PATH $ENV{QT_ROOT})
endif ()
set(CMAKE_PREFIX_PATH "${QT_ROOT_PATH}/mingw_64")

set(Qt6_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt6")

add_subdirectory(libs)
include(FetchContent)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(ApplicantStatsProject

        src/gui/main-widget.ui

        src/xlsx.h
        src/gui/window-manager.h
        src/gui/main-widget.h
        src/data-processing/table-manager.h
        src/data-processing/support-system.h
        src/data-processing/magic-hat.h
        src/applicants-faculthy-data/table-parser-bachelor.h
        src/applicants-faculthy-data/namespaces.h
        src/applicants-faculthy-data/faculthy-direction.h
        src/applicants-faculthy-data/applicant.h

        src/main.cpp
        src/gui/window-manager.cpp
        src/gui/main-widget.cpp
        src/data-processing/table-manager.cpp
        src/data-processing/support-system.cpp
        src/data-processing/magic-hat.cpp
        src/applicants-faculthy-data/table-parser-bachelor.cpp
        src/applicants-faculthy-data/faculthy-direction.cpp
        src/applicants-faculthy-data/applicant.cpp

        resources.qrc
)
target_link_libraries(ApplicantStatsProject PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        QXlsx::QXlsx
        Qt6::Charts
        $<$<PLATFORM_ID:Windows>:dwmapi>
)

if (WIN32)
    get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT windeployqt HINTS "${QT_BIN_DIR}")

    foreach (MINGW_DLL libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_BIN_DIR}/${MINGW_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
                COMMENT "Copying ${MINGW_DLL}..."
        )
    endforeach ()

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${WINDEPLOYQT}"
            --qmldir "${CMAKE_SOURCE_DIR}"
            --no-translations
            "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Running windeployqt..."
    )
endif ()