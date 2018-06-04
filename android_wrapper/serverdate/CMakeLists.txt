# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
set(CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release
cmake_minimum_required(VERSION 3.4.1)

# ==================================================================================================
# ==================================================================================================
# server_date_lib project
# ==================================================================================================
# ==================================================================================================

set(SOURCE_FILES
        ../../server_date/src/server_date.cpp)

include_directories(../../server_date/src)

add_library(server_date_native

                # Sets the library as a shared library.
                SHARED

                ${SOURCE_FILES})

find_library( # Sets the name of the path variable.
               log-lib

               # Specifies the name of the NDK library that
               # you want CMake to locate.
               log )

target_link_libraries( # Specifies the target library.
                       server_date_native

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       )

# ==================================================================================================
# ==================================================================================================
# SWIG wrapping for Java
# ==================================================================================================
# ==================================================================================================

# Fail the build if SWIG is not found - Ensure SWIG is installed and on the system path
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
# Ensure file recognized as C++ (otherwise, exported as C file)
set_property(SOURCE src/main/cpp/server_date_native.i PROPERTY CPLUSPLUS ON)
# Setup SWIG flags and locations
set(CMAKE_SWIG_FLAGS -c++ -package com.ubudu.serverdate.core)
set(CMAKE_SWIG_OUTDIR ${Project_SOURCE_DIR}/src/main/cpp/wrapper)
# Export a wrapper file to Java, and link with the created C++ library
swig_add_module(server_date_native_Wrapper java src/main/cpp/server_date_native.i)
swig_link_libraries(server_date_native_Wrapper server_date_native)
# Copy over the Java files to the correct directory
file(GLOB JAVA_FILES ${Project_SOURCE_DIR}/src/main/cpp/wrapper/*.java)
list(LENGTH JAVA_FILES NUM_FILES)
if(${NUM_FILES} GREATER 0)
    file(COPY ${JAVA_FILES} DESTINATION ${Project_SOURCE_DIR}/src/main/java/com/ubudu/serverdate/core)
    file(REMOVE ${JAVA_FILES})
endif()