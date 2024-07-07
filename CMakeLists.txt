cmake_minimum_required(VERSION 3.29.3)
project(server_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/usr/local/Qt-6.7.2/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia WebSockets Sql)
qt_standard_project_setup()

add_subdirectory(src/server)
add_subdirectory(src/database)
