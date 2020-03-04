set(pcg_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/pcg/include)

mark_as_advanced(pcg_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pcg
	REQUIRED_VARS pcg_INCLUDE_DIR
	VERSION_VAR pcg_VERSION
)

if(pcg_FOUND AND NOT TARGET pcg::pcg)
	add_library(pcg::pcg INTERFACE IMPORTED)
	set_target_properties(pcg::pcg PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${pcg_INCLUDE_DIR}
	)
endif()
