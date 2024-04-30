add_executable(client
                    client_main.cpp
                    client_main_window.cpp
                    client_manager.cpp
                    client_chat_window.cpp
                    chat_protocol.cpp
                    chat_line.cpp
                )

target_link_libraries(client PRIVATE database_library)

qt_add_resources(client "images"
                    PREFIX "/images"
                    FILES send_icon.png
                )
                
set_target_properties(client PROPERTIES MACOSX_BUNDLE ON)
