add_library(database_library STATIC database.cpp)  

target_link_libraries(database_library PUBLIC
                                        Qt6::Core 
                                        Qt6::Widgets
                                        Qt6::Multimedia
                                        Qt6::WebSockets
                                        Qt6::Sql
                        )

target_include_directories(database_library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
