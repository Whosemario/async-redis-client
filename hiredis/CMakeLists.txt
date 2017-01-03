cmake_minimum_required(VERSION 2.8)

set(HIREDIS_SRC
	async.h
	dict.h
	fmacros.h
	hiredis.h
	net.h
	read.h
	sds.h
	sdsalloc.h
	win32.h
	async.c
	dict.c
	hiredis.c
	net.c
	read.c
	sds.c
)

add_library(hiredis STATIC ${HIREDIS_SRC})
target_link_libraries(hiredis ws2_32)