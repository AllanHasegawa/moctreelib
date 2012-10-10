cmake_minimum_required(VERSION 2.8)

project(moctreelib-helloworld)

include_directories(${INCLUDE_DIRECTORIES} "../../sourcetree")
include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR})

set(SRCS
	helloworld.cpp
	)

add_executable(helloworld ${SRCS})
#link_libraries(helloworld moctreelib)
