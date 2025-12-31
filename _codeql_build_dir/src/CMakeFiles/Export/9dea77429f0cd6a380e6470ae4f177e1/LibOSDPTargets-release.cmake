#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libosdp::osdpstatic" for configuration "Release"
set_property(TARGET libosdp::osdpstatic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libosdp::osdpstatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libosdpstatic.a"
  )

list(APPEND _cmake_import_check_targets libosdp::osdpstatic )
list(APPEND _cmake_import_check_files_for_libosdp::osdpstatic "${_IMPORT_PREFIX}/lib/libosdpstatic.a" )

# Import target "libosdp::osdp" for configuration "Release"
set_property(TARGET libosdp::osdp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libosdp::osdp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libosdp.so.3.1.0"
  IMPORTED_SONAME_RELEASE "libosdp.so.3"
  )

list(APPEND _cmake_import_check_targets libosdp::osdp )
list(APPEND _cmake_import_check_files_for_libosdp::osdp "${_IMPORT_PREFIX}/lib/libosdp.so.3.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
