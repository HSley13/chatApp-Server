cmake_minimum_required(VERSION 3.28.3)
project(chat)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Core Network)
qt_standard_project_setup()

add_subdirectory(clients/)
add_subdirectory(server/)
