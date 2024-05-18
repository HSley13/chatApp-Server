# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "src/clients/CMakeFiles/client_autogen.dir/AutogenUsed.txt"
  "src/clients/CMakeFiles/client_autogen.dir/ParseCache.txt"
  "src/clients/client_autogen"
  "src/database/CMakeFiles/database_library_autogen.dir/AutogenUsed.txt"
  "src/database/CMakeFiles/database_library_autogen.dir/ParseCache.txt"
  "src/database/database_library_autogen"
  "src/server/CMakeFiles/server_autogen.dir/AutogenUsed.txt"
  "src/server/CMakeFiles/server_autogen.dir/ParseCache.txt"
  "src/server/server_autogen"
  )
endif()
