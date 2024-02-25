qt_add_executable(server
                    server.cpp
                    server_window.cpp
                    server_manager.cpp
                    chat_window.cpp
                )

target_link_libraries(server PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)

target_link_directories(server INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
