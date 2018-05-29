cmake_minimum_required(VERSION 3.9)
project(ubudu_location_algorithms)

set(SOURCE_FILES
        src/multilateration.cpp
        lib/alglib/src
        lib/alglib/src/alglibinternal.cpp
        lib/alglib/src/alglibmisc.cpp
        lib/alglib/src/ap.cpp
        lib/alglib/src/dataanalysis.cpp
        lib/alglib/src/diffequations.cpp
        lib/alglib/src/fasttransforms.cpp
        lib/alglib/src/integration.cpp
        lib/alglib/src/interpolation.cpp
        lib/alglib/src/linalg.cpp
        lib/alglib/src/optimization.cpp
        lib/alglib/src/solvers.cpp
        lib/alglib/src/specialfunctions.cpp
        lib/alglib/src/statistics.cpp
        src/tdoa.cpp
        src/mds.cpp src/loc_algo_error.h)

include_directories(lib/alglib/src)
include_directories(src)

add_library(ubudu_location_algorithms ${SOURCE_FILES})
