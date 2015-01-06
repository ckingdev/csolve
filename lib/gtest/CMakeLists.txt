set(SRC src/gtest-all.cc src/gtest_main.cc)

add_library(gtest ${SRC})
target_include_directories(gtest PUBLIC include)
target_link_libraries(gtest pthread)
