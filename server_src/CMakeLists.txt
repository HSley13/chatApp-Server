cmake_minimum_required(VERSION 3.29.3)
project(server_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Qt6 6.7.0 COMPONENTS Core Widgets Multimedia WebSockets)
qt_standard_project_setup()

qt_add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

target_link_libraries(server PRIVATE database_library)

qt_add_resources(server "images"
                    PREFIX "/images"
                    FILES send_icon.png
                )
     
set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)

add_subdirectory(database/)