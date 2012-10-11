# - Try to find MOctree
# Once done this will define
#  MOCTREE_FOUND - System has MOctree
#  MOCTREE_INCLUDE_DIRS - The MOctree include directories
#  MOCTREE_LIBRARIES - The libraries needed to use MOCtree
#  MOCTREE_DEFINITIONS - Compiler switches required for using MOCtree

find_path(MOCTREE_INCLUDE_DIR moctree/MOctree.h HINTS "/usr/local/include/moctree")

find_library(MOCTREE_LIBRARY NAMES moctree HINTS "/usr/local/lib/moctree")

set(MOCTREE_INCLUDE_DIRS ${MOCTREE_INCLUDE_DIR})
set(MOCTREE_LIBRARIES ${MOCTREE_LIBRARY})

include(FindPackageHandleStandardArgs)
