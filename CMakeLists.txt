project("csolve" CXX)
cmake_minimum_required(VERSION 3.0)

enable_testing()

include_directories(external)

set(GTEST_SRC external/gtest/gtest-all.cc external/gtest/gtest_main.cc)
add_library(gtest ${GTEST_SRC})
target_link_libraries(gtest pthread)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(SRC src/Puzzle.cpp)

add_library(libcsolve ${SRC})
target_compile_options(libcsolve PRIVATE -Wall -Werror)

set(EXEC_SRC src/main.cpp)

add_executable(csolve ${EXEC_SRC})
target_compile_options(csolve PRIVATE -Wall -Werror)
target_link_libraries(csolve libcsolve)

set(TEST_SRC src/test.cpp)
add_executable(csolve-test ${TEST_SRC} ${GTEST_SRC})
target_link_libraries(csolve-test libcsolve gtest)
add_test(csolve-test csolve-test)

set(2X2SERV_SRC src/2x2server.cpp)
add_executable(2x2server ${2X2SERV_SRC})
target_link_libraries(2x2server libcsolve)
