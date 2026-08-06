find_path(Shaderc_INCLUDE_DIR
  NAMES shaderc/shaderc.h
)

find_library(Shaderc_LIBRARY
  NAMES shaderc_shared
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Shaderc
  REQUIRED_VARS Shaderc_INCLUDE_DIR Shaderc_LIBRARY
)

if(Shaderc_FOUND AND NOT TARGET Shaderc::shaderc_shared)
  get_filename_component(Shaderc_LIBRARY_NAME "${Shaderc_LIBRARY}" NAME)

  add_library(Shaderc::shaderc_shared SHARED IMPORTED GLOBAL)
  set_target_properties(Shaderc::shaderc_shared PROPERTIES
    IMPORTED_LOCATION "${Shaderc_LIBRARY}"
    IMPORTED_LOCATION_RELEASE "${Shaderc_LIBRARY}"
    IMPORTED_SONAME_RELEASE "${Shaderc_LIBRARY_NAME}"
    INTERFACE_COMPILE_DEFINITIONS "SHADERC_SHAREDLIB"
    INTERFACE_INCLUDE_DIRECTORIES "${Shaderc_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(
  Shaderc_INCLUDE_DIR
  Shaderc_LIBRARY
)
