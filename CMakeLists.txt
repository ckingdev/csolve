project("csolve" CXX)
cmake_minimum_required(VERSION 3.0)

enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
add_subdirectory(lib)

set(SRC src/Puzzle.cpp)

add_library(libcsolve ${SRC})
target_compile_options(libcsolve PRIVATE -Wall -Werror)
target_include_directories(libcsolve PUBLIC include)
target_link_libraries(libcsolve cereal)

set(EXEC_SRC src/main.cpp)

add_executable(csolve ${EXEC_SRC})
target_link_libraries(csolve libcsolve)

set(TEST_SRC test/test.cpp)

add_executable(csolve-test ${TEST_SRC})

set(2X2SERV_SRC src/2x2server.cpp)
add_executable(2x2server ${2X2SERV_SRC})
target_link_libraries(2x2server libcsolve)

target_link_libraries(csolve-test libcsolve gtest)
add_test(csolve-test csolve-test)
