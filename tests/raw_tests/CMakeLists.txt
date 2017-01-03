cmake_minimum_required(VERSION 2.8)

add_executable(go_simple_test go_simple_test.cpp)
target_link_libraries(go_simple_test ${libgo_link})

