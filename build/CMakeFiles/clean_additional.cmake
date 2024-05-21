# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src/database/CMakeFiles/database_library_autogen.dir/AutogenUsed.txt"
  "src/database/CMakeFiles/database_library_autogen.dir/ParseCache.txt"
  "src/database/database_library_autogen"
  "src/server/CMakeFiles/server_autogen.dir/AutogenUsed.txt"
  "src/server/CMakeFiles/server_autogen.dir/ParseCache.txt"
  "src/server/server_autogen"
  )
endif()
