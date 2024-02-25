cmake_minimum_required(VERSION 3.28.1)
project(server_clients)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Core Network REQUIRED)
qt_standard_project_setup()

add_subdirectory(server/)
add_subdirectory(clients/)