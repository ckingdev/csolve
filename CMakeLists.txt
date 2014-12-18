project("csolve" CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")
set(SRC main.cpp Puzzle.cpp PruningTable.cpp)

add_executable(csolve ${SRC})
target_compile_options(csolve PRIVATE -Wall -Werror)

#add_executable(debug ${SRC})
#target_compile_options(debug PRIVATE -g -pg)

# Google Test
include_directories(.)
add_library(gtest gtest/gtest_main.cc gtest/gtest-all.cc)
target_link_libraries(gtest pthread)

set(TESTSRC Puzzle.cpp test.cpp)
add_executable(test ${TESTSRC})
target_link_libraries(test gtest)