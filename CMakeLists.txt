cmake_minimum_required(VERSION 3.20.0)

project(sklib_uuid VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/sklib_base.cmake)

add_subdirectory(generated)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(install)
