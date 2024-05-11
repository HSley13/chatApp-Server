qt_add_executable(client
                    client_main.cpp
                    client_main_window.cpp
                    client_manager.cpp
                    client_chat_window.cpp
                    chat_protocol.cpp
                    chat_line.cpp
                )


target_link_libraries(client PRIVATE database_library)


qt_add_resources(client "client_images"
                    PREFIX "/images"
                    FILES send_icon.png file_icon.webp record_icon.png online.jpeg offline.jpeg
                )

set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)

set_target_properties(client PROPERTIES MACOSX_BUNDLE ON  MACOSX_BUNDLE_INFO_PLIST ${MACOSX_BUNDLE_INFO_PLIST})