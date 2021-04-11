file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )

foreach(sourcefile ${APP_SOURCES})
  string(REPLACE ".cpp" "" testname  ${sourcefile})
  add_executable(${testname} ${sourcefile})
endforeach( sourcefile ${APP_SOURCES})
