cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(ZTGUnitManager VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Google Test ##################################################################

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(external/googletest)

################################################################################

# ALEPH ########################################################################

#if(NOT DEFINED ENV{ALEPHW})
#  message(FATAL_ERROR "ALEPHW environment variable is not defined")
#endif()

#find_library(ALEPH_LIBRARY
#  NAMES aleph Aleph
#  PATHS ENV ALEPHW
#)

#if(NOT ALEPH_LIBRARY)
#  message(FATAL_ERROR "ALEPHW library not found")
#endif()

################################################################################

set(COMPILER_WARN_OPTS
    "-Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses")

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_WARN_OPTS} -g")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(test)