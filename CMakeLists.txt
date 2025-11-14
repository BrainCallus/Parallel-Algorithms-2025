cmake_minimum_required(VERSION 3.28)
project(Parallel_Algorithms_2025 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        parlaylib
        GIT_REPOSITORY https://github.com/cmuparlay/parlaylib.git
)
FetchContent_MakeAvailable(parlaylib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O3")

add_executable(Parallel_Algorithms_2025 qsort/quick_sort.cpp
        qsort/utils.cpp
        qsort/runs.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND WIN32)
    message(STATUS "Applying MinGW linker workaround: allow multiple definitions")
    target_link_options(Parallel_Algorithms_2025 PRIVATE "-Wl,--allow-multiple-definition")
endif ()


find_package(Threads REQUIRED)
target_link_libraries(Parallel_Algorithms_2025 PRIVATE Threads::Threads)

if (DEFINED parlaylib_SOURCE_DIR)
    message(STATUS "parlaylib source dir: ${parlaylib_SOURCE_DIR}")
    message(STATUS "parlaylib binary dir: ${parlaylib_BINARY_DIR}")
else ()
    message(WARNING "parlaylib_SOURCE_DIR is not defined — FetchContent failed or not populated yet")
endif ()

if (TARGET parlay)
    target_link_libraries(Parallel_Algorithms_2025 PRIVATE parlay)
elseif (TARGET parlaylib)
    target_link_libraries(Parallel_Algorithms_2025 PRIVATE parlaylib)
elseif (TARGET parlay_library)
    target_link_libraries(Parallel_Algorithms_2025 PRIVATE parlay_library)
else ()
    if (DEFINED parlaylib_SOURCE_DIR)
        target_include_directories(Parallel_Algorithms_2025 PRIVATE
                ${parlaylib_SOURCE_DIR}/include
        )
        message(STATUS "parlay CMake target not found — added include dir ${parlaylib_SOURCE_DIR}/include as fallback")
    else ()
        message(WARNING "parlaylib source dir not available; check FetchContent output")
    endif ()
endif ()



