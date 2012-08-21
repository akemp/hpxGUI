cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(hpxgui CXX)

include_directories(${CMAKE_SOURCE_DIR})

################################################################################
# Build type (needs to be handled before project command below)
################################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Configuration type (one of Debug, RelWithDebInfo, Release, MinSizeRel)" FORCE)
endif()

set(HPX_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Configuration type (one of Debug, RelWithDebInfo, Release, MinSizeRel)" FORCE)

################################################################################

# TODO: Move this into a CMake macro.
if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/lib/hpx)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/hpx)
endif()

################################################################################
# TODO: Move this into FindHPX.cmake.in.
if(NOT HPX_ROOT)
  if(NOT $ENV{HPX_LOCATION} STREQUAL "")
    set(HPX_ROOT $ENV{HPX_LOCATION})
  elseif(NOT $ENV{HPX_ROOT} STREQUAL "")
    set(HPX_ROOT $ENV{HPX_ROOT})
  endif()
endif()

set(HPX_ROOT "${HPX_ROOT}" CACHE PATH "The HPX installation to use." FORCE)

set(CMAKE_MODULE_PATH ${HPX_ROOT}/share/cmake-2.8/Modules)

find_package(HPX)

foreach(dir ${HPX_INCLUDE_DIR})
  include_directories(${dir})
endforeach()

foreach(dir ${HPX_LIBRARY_DIR})
  link_directories(${dir})
endforeach()

set(CMAKE_BUILD_TYPE ${HPX_BUILD_TYPE} CACHE STRING "Build type." FORCE)

add_subdirectory(examples)

if(NOT ${OCLM_FOUND})
   message(ERROR ": OCLM NOT FOUND!")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

################################################################################
# Install include directory
################################################################################
MACRO(SUBDIRCOPY curdir)
  FILE(GLOB children ${curdir}/ ${curdir}/*)
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
       # Install include subdirectories
       FILE(GLOB files "${curdir}/${child}/*.hpp")
       STRING(REPLACE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/include bindir ${curdir}/${child})
       INSTALL(FILES ${files} DESTINATION ${bindir})
       SUBDIRCOPY("${curdir}/${child}")
    ENDIF()
  ENDFOREACH()
ENDMACRO()

SUBDIRCOPY(${CMAKE_SOURCE_DIR}/include/)