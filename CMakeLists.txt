# ------------------------------------------------------------------------------ #
#                                Project setup                                   #
# ------------------------------------------------------------------------------ #

cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME "TAiO_Project")

set(MAIN ${PROJECT_NAME})
set(TEST ${PROJECT_NAME}_test)
set(LIB ${PROJECT_NAME}_lib)

project(${PROJECT_NAME} LANGUAGES C CXX)

set(PROJECT_VERSION "1.0")
set(PROJECT_AUTHOR "Mateusz Mikiciuk & Mykhailo Shamrai")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------ #
#                                  Load dirs                                     #
# ------------------------------------------------------------------------------ #

add_subdirectory(project)
add_subdirectory(dependencies)
add_subdirectory(tests)
enable_testing()