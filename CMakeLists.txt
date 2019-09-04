cmake_minimum_required(VERSION 2.8.12)
project( cpp_templates )

# add gcc standard
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11" )
# add g++ standard
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3 -Wall -lpthread -lutil" )

include_directories( "${PROJECT_SOURCE_DIR}" )

# subdirectories in project
add_subdirectory( lib )
add_subdirectory( problems )
add_subdirectory( test )
