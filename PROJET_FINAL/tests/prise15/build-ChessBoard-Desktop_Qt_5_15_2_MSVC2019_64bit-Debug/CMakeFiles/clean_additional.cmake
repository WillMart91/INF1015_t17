# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ChessBoard_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ChessBoard_autogen.dir\\ParseCache.txt"
  "ChessBoard_autogen"
  )
endif()
