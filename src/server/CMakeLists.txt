qt_add_executable(${PROJECT_NAME}
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

target_link_libraries(${PROJECT_NAME} PRIVATE database_library)

qt_add_resources(${PROJECT_NAME} "images"
                    PREFIX "/images"
                    FILES send_icon.png file_icon.webp
                )
     
if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}>
    ${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    include_directories(${EMSCRIPTEN}/system/include)
endif()