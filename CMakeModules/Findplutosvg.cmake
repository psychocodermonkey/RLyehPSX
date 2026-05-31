find_path(plutosvg_INCLUDE_DIR
    NAMES plutosvg.h
)

find_library(plutosvg_LIBRARY
    NAMES plutosvg libplutosvg
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(plutosvg
    REQUIRED_VARS plutosvg_INCLUDE_DIR plutosvg_LIBRARY
)

if (plutosvg_FOUND AND NOT TARGET plutosvg::plutosvg)
    add_library(plutosvg::plutosvg UNKNOWN IMPORTED GLOBAL)
    set_target_properties(plutosvg::plutosvg PROPERTIES
        IMPORTED_LOCATION "${plutosvg_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${plutosvg_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(
    plutosvg_INCLUDE_DIR
    plutosvg_LIBRARY
)
