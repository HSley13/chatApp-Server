cmake_minimum_required(VERSION 3.29.2)
project(chat_application LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Qt6 6.7.0 REQUIRED COMPONENTS Core Widgets Network Multimedia WebSockets)
qt_standard_project_setup()

add_subdirectory(src/clients/)
add_subdirectory(src/server/)
add_subdirectory(src/database/)