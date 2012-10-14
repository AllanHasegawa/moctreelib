project(moctree_marching_cubes)

FIND_PACKAGE(wxWidgets REQUIRED base core gl)
INCLUDE(${wxWidgets_USE_FILE})


set(SRCS
	marching_cubes.cpp)
set(DEPS
	${wxWidgets_LIBRARIES})

add_executable(moctree_marching_cubes ${SRCS})
target_link_libraries(moctree_marching_cubes ${DEPS})
