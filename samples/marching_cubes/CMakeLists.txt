cmake_minimum_required(VERSION 2.8)

project(moctree_marching_cubes)

FIND_PACKAGE(wxWidgets REQUIRED core base gl)
INCLUDE(${wxWidgets_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/modules/")
find_package(MOctree REQUIRED)
include_directories(${MOCTREE_INCLUDE_DIRS})


set(SRCS
	marching_cubes.cpp
	CanvasWindow.cpp
	Camera.cpp
	MarchingCubes.cpp
	MarchingCubesUniques.cpp
	MCTemplate.cpp
	Triangle.cpp)
	
set(DEPS
	${wxWidgets_LIBRARIES}
	${MOctree_LIBRARIES})

add_executable(moctree_marching_cubes ${SRCS})
target_link_libraries(moctree_marching_cubes ${DEPS})
