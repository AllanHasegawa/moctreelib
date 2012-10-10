cmake_minimum_required(VERSION 2.8)

############
# Macro "add_sources(<src1> <src2> ...)"
#
# call this method inside the source directory, with it,
# relative to that directory :)
############
set(SRCS "" CACHE INTERNAL "")

macro (add_sources)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} _nativePath)
    
    foreach(_src ${ARGN})
        list (APPEND SRCS "${_nativePath}/${_src}")
    endforeach()
    
    set (SRCS ${SRCS} CACHE INTERNAL "")
endmacro()


project(moctreelib)

include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR})


add_subdirectory(moctree)

message(STATUS ${SRCS})

#add_library(moctreelib SHARED ${SRCS})
