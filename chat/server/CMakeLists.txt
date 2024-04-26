add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

target_link_libraries(server PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                        database_library
                    )

set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)
