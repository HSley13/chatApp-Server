qt_add_executable(client_3 
                    client_3.cpp
                    client_3_window.cpp
                )

target_link_libraries(client_3 PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(client_3 PROPERTIES MACOSX_BUNDLE ON)

target_link_directories(client_3 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
