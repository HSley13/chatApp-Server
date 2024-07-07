qt_add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

target_link_libraries(server PRIVATE database_library)

qt_add_resources(server "images"
                    PREFIX "/images"
                    FILES send_icon.png
                )
     
set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)

add_custom_command(TARGET server POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            $<TARGET_FILE:server>
                            ${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:server>
                    )

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    include_directories(${EMSCRIPTEN}/system/include)
    set_target_properties(server PROPERTIES LINK_FLAGS "-lidbfs.js")
endif()