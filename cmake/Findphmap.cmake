set(phmap_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/phmap/parallel_hashmap/)

mark_as_advanced(phmap_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(phmap
	REQUIRED_VARS phmap_INCLUDE_DIR
	VERSION_VAR phmap_VERSION
)

if(phmap_FOUND)
	get_filename_component(phmap_INCLUDE_DIRS ${phmap_INCLUDE_DIR} DIRECTORY)
endif()

if(phmap_FOUND AND NOT TARGET phmap::phmap)
	add_library(phmap::phmap INTERFACE IMPORTED)
	set_target_properties(phmap::phmap PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${phmap_INCLUDE_DIRS}
	)
endif()
