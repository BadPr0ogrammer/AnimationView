#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ElevationFilters" for configuration ""
set_property(TARGET ElevationFilters APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ElevationFilters PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/libElevationFilters.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ElevationFilters )
list(APPEND _IMPORT_CHECK_FILES_FOR_ElevationFilters "${_IMPORT_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/libElevationFilters.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
