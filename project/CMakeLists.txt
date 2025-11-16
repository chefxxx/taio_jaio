message("Loading project...")

# ------------------------------------------------------------------------------ #
# Gather source files #
# ------------------------------------------------------------------------------ #

file(GLOB CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

# ------------------------------------------------------------------------------ #
# Define cxx lib #
# ------------------------------------------------------------------------------ #

message("Loading CXX library...")

add_library(${LIB} STATIC ${CXX_SOURCES})
target_include_directories(${LIB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${LIB} PUBLIC spdlog::spdlog)

# ------------------------------------------------------------------------------ #
# Define executable #
# ------------------------------------------------------------------------------ #

add_executable(${MAIN} main.cpp)
target_link_libraries(${MAIN} PRIVATE ${LIB})

# ------------------------------------------------------------------------------ #
# Compilation settings #
# ------------------------------------------------------------------------------ #

# Set build type to RELEASE by default:
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type provided, default to RELEASE.")
    set(CMAKE_BUILD_TYPE "RELEASE")
endif ()

message("Build type: " "${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message("Using GNU compiler...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("Using Clang...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message("Using MSVC...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        message("Using AppleClang...")
    else ()
        message(FATAL_ERROR "Compiler " "${CXX_COMPILER_ID}" " is not supported.")
    endif ()

    target_compile_options(${LIB} PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-g -O0 -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Werror>
            $<$<CXX_COMPILER_ID:Clang>:-g -O0 -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Werror>
            $<$<CXX_COMPILER_ID:AppleClang>:-g -O0 -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Werror>
            $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message("Using GNU compiler...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("Using Clang...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message("Using MSVC...")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        message("Using AppleClang...")
    else ()
        message(FATAL_ERROR "Compiler " "${CXX_COMPILER_ID}" " is not supported.")
    endif ()

    target_compile_options(${LIB} PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-O3 -march=native -funroll-loops>
            $<$<CXX_COMPILER_ID:Clang>:-O3 -march=native -funroll-loops>
            $<$<CXX_COMPILER_ID:AppleClang>:-O3 -march=native -funroll-loops>
            $<$<CXX_COMPILER_ID:MSVC>:> 
    )

else()
    message(FATAL_ERROR "Unknown build type.")
endif ()
