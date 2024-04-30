cmake_minimum_required(VERSION 3.29.2)
project(chat_application)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)
qt_standard_project_setup()

add_subdirectory(src/clients/)
add_subdirectory(src/server/)
add_subdirectory(src/database/)