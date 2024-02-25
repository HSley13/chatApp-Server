cmake_minimum_required(VERSION 3.28.1)
project(server_clients)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Core Network REQUIRED)
qt_standard_project_setup()

add_subdirectory(client_1/)
add_subdirectory(client_2/)
add_subdirectory(client_3/)
add_subdirectory(server/)