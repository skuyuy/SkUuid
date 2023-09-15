include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS ${_SK_MODULE_NAME}
        EXPORT sklibUuidTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# headers will be installed globally, see install/CMakeLists.txt

install(EXPORT sklibUuidTargets
        FILE sklibUuidTargets.cmake
        NAMESPACE sklib::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sklib)

message(STATUS ${CMAKE_INSTALL_INCLUDEDIR})
message(STATUS ${CMAKE_INSTALL_LIBDIR})
message(STATUS ${CMAKE_INSTALL_BINDIR})

# install the whole include directory to cover all libraries
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        TYPE INCLUDE
        FILES_MATCHING PATTERN "*.hpp")

configure_package_config_file(Config.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/sklibUuidConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sklib)
write_basic_package_version_file(sklibUuidConfigVersion.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY AnyNewerVersion ARCH_INDEPENDENT)

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/sklibUuidConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/sklibUuidConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sklib)
