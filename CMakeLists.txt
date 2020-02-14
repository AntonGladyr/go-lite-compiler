project(golite)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

include_directories(include)
include_directories(tests)
set(CMAKE_SOURCE_DIR src)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/frontEnd)

bison_target(GoLiteParser ${CMAKE_SOURCE_DIR}/frontEnd/golite.y ${CMAKE_CURRENT_BINARY_DIR}/frontEnd/GoLite_Parser.cpp)
flex_target(GoLiteScanner ${CMAKE_SOURCE_DIR}/frontEnd/golite.l ${CMAKE_CURRENT_BINARY_DIR}/frontEnd/GoLite_Scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(GoLiteScanner GoLiteParser)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(golite ${SOURCES} ${BISON_GoLiteParser_OUTPUTS} ${FLEX_GoLiteScanner_OUTPUTS})
