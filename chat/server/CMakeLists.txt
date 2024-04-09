add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

# Enable AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(ENV{ASAN_OPTIONS} "symbolize=1:stack_trace_format=%f:%l:abort_on_error=1")

set(ENV{ASAN_OPTIONS} "print_stack_trace=1")

target_link_libraries(server PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                        -fsanitize=address
                    )

set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)
