# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/test/Documents/server---clients/chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/test/Documents/server---clients/build

# Include any dependencies generated for this target.
include server/CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server/CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include server/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/server.dir/flags.make

server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o: server/server_autogen/mocs_compilation.cpp
server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o -MF CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o -c /Users/test/Documents/server---clients/build/server/server_autogen/mocs_compilation.cpp

server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/build/server/server_autogen/mocs_compilation.cpp > CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.i

server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/build/server/server_autogen/mocs_compilation.cpp -o CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.s

server/CMakeFiles/server.dir/server_main.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/server_main.cpp.o: /Users/test/Documents/server---clients/chat/server/server_main.cpp
server/CMakeFiles/server.dir/server_main.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object server/CMakeFiles/server.dir/server_main.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/server_main.cpp.o -MF CMakeFiles/server.dir/server_main.cpp.o.d -o CMakeFiles/server.dir/server_main.cpp.o -c /Users/test/Documents/server---clients/chat/server/server_main.cpp

server/CMakeFiles/server.dir/server_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server_main.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/server_main.cpp > CMakeFiles/server.dir/server_main.cpp.i

server/CMakeFiles/server.dir/server_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server_main.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/server_main.cpp -o CMakeFiles/server.dir/server_main.cpp.s

server/CMakeFiles/server.dir/server_main_window.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/server_main_window.cpp.o: /Users/test/Documents/server---clients/chat/server/server_main_window.cpp
server/CMakeFiles/server.dir/server_main_window.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object server/CMakeFiles/server.dir/server_main_window.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/server_main_window.cpp.o -MF CMakeFiles/server.dir/server_main_window.cpp.o.d -o CMakeFiles/server.dir/server_main_window.cpp.o -c /Users/test/Documents/server---clients/chat/server/server_main_window.cpp

server/CMakeFiles/server.dir/server_main_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server_main_window.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/server_main_window.cpp > CMakeFiles/server.dir/server_main_window.cpp.i

server/CMakeFiles/server.dir/server_main_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server_main_window.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/server_main_window.cpp -o CMakeFiles/server.dir/server_main_window.cpp.s

server/CMakeFiles/server.dir/server_manager.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/server_manager.cpp.o: /Users/test/Documents/server---clients/chat/server/server_manager.cpp
server/CMakeFiles/server.dir/server_manager.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object server/CMakeFiles/server.dir/server_manager.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/server_manager.cpp.o -MF CMakeFiles/server.dir/server_manager.cpp.o.d -o CMakeFiles/server.dir/server_manager.cpp.o -c /Users/test/Documents/server---clients/chat/server/server_manager.cpp

server/CMakeFiles/server.dir/server_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server_manager.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/server_manager.cpp > CMakeFiles/server.dir/server_manager.cpp.i

server/CMakeFiles/server.dir/server_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server_manager.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/server_manager.cpp -o CMakeFiles/server.dir/server_manager.cpp.s

server/CMakeFiles/server.dir/server_chat_window.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/server_chat_window.cpp.o: /Users/test/Documents/server---clients/chat/server/server_chat_window.cpp
server/CMakeFiles/server.dir/server_chat_window.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object server/CMakeFiles/server.dir/server_chat_window.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/server_chat_window.cpp.o -MF CMakeFiles/server.dir/server_chat_window.cpp.o.d -o CMakeFiles/server.dir/server_chat_window.cpp.o -c /Users/test/Documents/server---clients/chat/server/server_chat_window.cpp

server/CMakeFiles/server.dir/server_chat_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server_chat_window.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/server_chat_window.cpp > CMakeFiles/server.dir/server_chat_window.cpp.i

server/CMakeFiles/server.dir/server_chat_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server_chat_window.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/server_chat_window.cpp -o CMakeFiles/server.dir/server_chat_window.cpp.s

server/CMakeFiles/server.dir/chat_line.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/chat_line.cpp.o: /Users/test/Documents/server---clients/chat/server/chat_line.cpp
server/CMakeFiles/server.dir/chat_line.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object server/CMakeFiles/server.dir/chat_line.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/chat_line.cpp.o -MF CMakeFiles/server.dir/chat_line.cpp.o.d -o CMakeFiles/server.dir/chat_line.cpp.o -c /Users/test/Documents/server---clients/chat/server/chat_line.cpp

server/CMakeFiles/server.dir/chat_line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/chat_line.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/chat_line.cpp > CMakeFiles/server.dir/chat_line.cpp.i

server/CMakeFiles/server.dir/chat_line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/chat_line.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/chat_line.cpp -o CMakeFiles/server.dir/chat_line.cpp.s

server/CMakeFiles/server.dir/chat_protocol.cpp.o: server/CMakeFiles/server.dir/flags.make
server/CMakeFiles/server.dir/chat_protocol.cpp.o: /Users/test/Documents/server---clients/chat/server/chat_protocol.cpp
server/CMakeFiles/server.dir/chat_protocol.cpp.o: server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object server/CMakeFiles/server.dir/chat_protocol.cpp.o"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/server.dir/chat_protocol.cpp.o -MF CMakeFiles/server.dir/chat_protocol.cpp.o.d -o CMakeFiles/server.dir/chat_protocol.cpp.o -c /Users/test/Documents/server---clients/chat/server/chat_protocol.cpp

server/CMakeFiles/server.dir/chat_protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/chat_protocol.cpp.i"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/test/Documents/server---clients/chat/server/chat_protocol.cpp > CMakeFiles/server.dir/chat_protocol.cpp.i

server/CMakeFiles/server.dir/chat_protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/chat_protocol.cpp.s"
	cd /Users/test/Documents/server---clients/build/server && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/test/Documents/server---clients/chat/server/chat_protocol.cpp -o CMakeFiles/server.dir/chat_protocol.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/server.dir/server_main.cpp.o" \
"CMakeFiles/server.dir/server_main_window.cpp.o" \
"CMakeFiles/server.dir/server_manager.cpp.o" \
"CMakeFiles/server.dir/server_chat_window.cpp.o" \
"CMakeFiles/server.dir/chat_line.cpp.o" \
"CMakeFiles/server.dir/chat_protocol.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/server_autogen/mocs_compilation.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/server_main.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/server_main_window.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/server_manager.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/server_chat_window.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/chat_line.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/chat_protocol.cpp.o
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/build.make
server/server.app/Contents/MacOS/server: /opt/homebrew/lib/QtWidgets.framework/Versions/A/QtWidgets
server/server.app/Contents/MacOS/server: /opt/homebrew/lib/QtNetwork.framework/Versions/A/QtNetwork
server/server.app/Contents/MacOS/server: /opt/homebrew/lib/QtGui.framework/Versions/A/QtGui
server/server.app/Contents/MacOS/server: /opt/homebrew/lib/QtCore.framework/Versions/A/QtCore
server/server.app/Contents/MacOS/server: server/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/test/Documents/server---clients/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable server.app/Contents/MacOS/server"
	cd /Users/test/Documents/server---clients/build/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/server.dir/build: server/server.app/Contents/MacOS/server
.PHONY : server/CMakeFiles/server.dir/build

server/CMakeFiles/server.dir/clean:
	cd /Users/test/Documents/server---clients/build/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/server.dir/clean

server/CMakeFiles/server.dir/depend:
	cd /Users/test/Documents/server---clients/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/test/Documents/server---clients/chat /Users/test/Documents/server---clients/chat/server /Users/test/Documents/server---clients/build /Users/test/Documents/server---clients/build/server /Users/test/Documents/server---clients/build/server/CMakeFiles/server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : server/CMakeFiles/server.dir/depend

