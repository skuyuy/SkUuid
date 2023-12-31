# module.cmake
# creates a module in form of a linkable library
# usage:
#
# set(MODULE_NAME FooModule)
# set(MODULE_SOURCE foo.cpp foo.h)
# set(MODULE_INCLUDE ${CMAKE_SOURCE_DIR}/bar)
# set(MODULE_DEFINITIONS MODULE="Foo")
# set(MODULE_LINK bar::bar)
#
# include(.../module.cmake)

message(STATUS "Configuring module: ${MODULE_NAME}")

# create the library target
add_library(${MODULE_NAME})
# create an alias for the target without the prefix
target_sources(${MODULE_NAME} PRIVATE ${MODULE_SOURCE})
target_include_directories(${MODULE_NAME} PUBLIC ${_SKLIB_INCLDIR})
target_include_directories(${MODULE_NAME} PRIVATE ${CMAKE_BINARY_DIR} ${MODULE_INCLUDE})
target_compile_definitions(${MODULE_NAME} PUBLIC
    MODULE_NAME="${MODULE_NAME}"
    ${MODULE_DEFINITIONS})
target_link_libraries(${MODULE_NAME} PRIVATE ${MODULE_LINK})

# create library test target if MODULE_TEST is ON
# if(${MODULE_TEST})
#     add_executable(${_SKLIB_MODULE_NAME}_test ${CMAKE_SOURCE_DIR}/test/main.cpp)
#     target_link_libraries(${_SKLIB_MODULE_NAME}_test PUBLIC ${_SKLIB_MODULE_NAME} ${MODULE_LINK})
#     target_include_directories(${_SKLIB_MODULE_NAME}_test PUBLIC ${_SKLIB_INCLDIR})
#     target_include_directories(${_SKLIB_MODULE_NAME}_test PRIVATE ${CMAKE_BINARY_DIR} ${MODULE_INCLUDE})
#     target_compile_definitions(${_SKLIB_MODULE_NAME}_test PUBLIC
#         ${MODULE_DEFINITIONS})
# endif()
