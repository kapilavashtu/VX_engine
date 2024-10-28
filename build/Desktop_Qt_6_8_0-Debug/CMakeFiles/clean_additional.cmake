# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appvx_engine_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appvx_engine_autogen.dir/ParseCache.txt"
  "appvx_engine_autogen"
  )
endif()
