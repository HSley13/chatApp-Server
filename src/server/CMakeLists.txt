add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

target_link_libraries(server PRIVATE database_library)
                    
set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)
