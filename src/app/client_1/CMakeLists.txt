qt_add_executable(client_1 
                    client_1.cpp
                    client_1_window.cpp
                )

target_link_libraries(client_1 PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(client_1 PROPERTIES MACOSX_BUNDLE ON)

target_link_directories(client_1 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
