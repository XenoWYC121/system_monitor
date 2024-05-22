cmake_minimum_required(VERSION 3.20)

if (IN_DOCKER_ENV)
    message("ok")
else ()
    project(qt_monitor VERSION 0.1)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)


    find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

    set(
            PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            monitorwidget.cpp
            inputaddress.cpp
            mainwindow.ui
            monitorwidget.ui
            inputaddress.ui
            ${HEADERS}
    )

    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES})

    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core proto_lib sys_info_client cpu_usage_client memory_usage_client)

endif ()