set(_SK_MODULE_TEST ${_SK_MODULE_NAME}-test)

add_executable(${_SK_MODULE_TEST} main.cpp)
target_link_libraries(${_SK_MODULE_TEST} PUBLIC ${_SK_MODULE_NAME})
target_include_directories(${_SK_MODULE_TEST} PUBLIC ${_SKLIB_INCLDIR})
