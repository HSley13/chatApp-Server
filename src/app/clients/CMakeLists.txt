qt_add_executable(client
                    client.cpp
                    client_window.cpp
                    client_manager.cpp
                )

target_link_libraries(client PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(client PROPERTIES MACOSX_BUNDLE ON)

target_link_directories(client INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
