add_executable(server
                    server_main.cpp
                    server_main_window.cpp
                    server_manager.cpp
                    server_chat_window.cpp
                    chat_line.cpp
                    chat_protocol.cpp
                )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

# set(ENV{ASAN_OPTIONS} "symbolize = 1: stack_trace_format = '%f:%l': abort_on_error = 1: print_stack_trace = 1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

target_link_libraries(server PRIVATE
                        Qt6::Widgets
                        Qt6::Core
                        Qt6::Network
                    )

set_target_properties(server PROPERTIES MACOSX_BUNDLE ON)
