cmake_minimum_required(VERSION 3.29.3)
project(server_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Qt6 6.7.0 COMPONENTS Core Widgets Multimedia WebSockets)
qt_standard_project_setup()

add_subdirectory(src/server/)
add_subdirectory(src/clients/)
add_subdirectory(src/database/)