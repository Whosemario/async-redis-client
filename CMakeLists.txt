cmake_minimum_required(VERSION 2.8)

project(async_redis_client)

if (CMAKE_BUILD_TYPE)
else()
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

# libgo
if (WIN32)
	set(LIBGO_LIB ${PROJECT_SOURCE_DIR}/libgo/lib/win32)
endif ()
include_directories(${PROJECT_SOURCE_DIR}/libgo/include)
link_directories(${LIBGO_LIB})
set(libgo_link libgo)
# end  libgo

# python
if (WIN32)
	set(PYTHON_INC ${PYTHON_ROOT}/include)
	set(PYTHON_LIB ${PYTHON_ROOT}/libs)
	set(python_link python27)
endif ()
include_directories(${PYTHON_INC})
link_directories(${PYTHON_LIB})
# end python

# cflags
if (WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif ()
# end cflags

message("------------ info -------------")
message("  CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("  Libgo include dir: ${PROJECT_SOURCE_DIR}/libgo/include}")
message("  Libgo lib dir: ${LIBGO_LIB}")
message("  Libgo link: ${libgo_link}")
message("  Python include dir: ${PYTHON_INC}")
message("  Python lib dir: ${PYTHON_LIB}")
message("  Python link: ${python_link}")
message("  CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("  CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("----------------------------------")

set(PYTHON_BINDING_SRCS
	python/redis.cpp
)
add_library(redis MODULE ${PYTHON_BINDING_SRCS})
if(WIN32)
	set_target_properties(redis PROPERTIES SUFFIX ".pyd")
endif()
target_link_libraries(redis ${python_link} ${libgo_link})

# test
add_subdirectory(tests)