add_executable(client
                    client_main.cpp
                    client_main_window.cpp
                    client_manager.cpp
                    client_chat_window.cpp
                    chat_protocol.cpp
                    chat_line.cpp
                )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

target_link_libraries(client PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                        database_library
                    )

set_target_properties(client PROPERTIES MACOSX_BUNDLE ON)