cmake_minimum_required(VERSION 2.8)

add_executable(go_simple_test go_simple_test.cpp)
if (WIN32)
	target_link_libraries(go_simple_test ${libgo_link} ws2_32)
endif ()
set_target_properties(go_simple_test PROPERTIES COMPILE_FLAGS "/wd4819 /wd4267")

