cmake_minimum_required(VERSION 2.8)

project(moctreelib-helloworld)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/modules/")

find_package(MOctree REQUIRED)

include_directories(${MOCTREE_INCLUDE_DIRS})

set(SRCS
	helloworld.cpp
	)

add_executable(helloworld ${SRCS})
#link_libraries(helloworld moctreelib)
