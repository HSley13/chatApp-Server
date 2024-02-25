qt_add_executable(client_2 
                    client_2.cpp
                    client_2_window.cpp
                )

target_link_libraries(client_2 PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(client_2 PROPERTIES MACOSX_BUNDLE ON)

target_link_directories(client_2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})