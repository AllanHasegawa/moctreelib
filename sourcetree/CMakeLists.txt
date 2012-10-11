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

############
# Macro "add_headers(<src1> <src2> ...)"
#
# call this method inside the header directory, with it,
# relative to that directory :)
############
set(HDRS "" CACHE INTERNAL "")

macro (add_headers)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} _nativePath)
    
    foreach(_src ${ARGN})
        list (APPEND HDRS "${_nativePath}/${_src}")
    endforeach()
    
    set (HDRS ${HDRS} CACHE INTERNAL "")
endmacro()


project(moctree)

include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR})

add_subdirectory(moctree)

add_sources(ignore.cpp)

add_library(moctree SHARED ${SRCS})

install(TARGETS moctree DESTINATION lib/${CMAKE_PROJECT_NAME})

# Export the moctree header files
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/moctree/*.h")
INSTALL(FILES ${files} DESTINATION include/${CMAKE_PROJECT_NAME}/moctree)

# Export the moctree/classic header files
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/moctree/classic/*.h")
INSTALL(FILES ${files} DESTINATION include/${CMAKE_PROJECT_NAME}/moctree/classic)


