set(sajson_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/sajson/include)

mark_as_advanced(sajson_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sajson
	REQUIRED_VARS sajson_INCLUDE_DIR
	VERSION_VAR sajson_VERSION
)

if(sajson_FOUND AND NOT TARGET sajson::sajson)
	add_library(sajson::sajson INTERFACE IMPORTED)
	set_target_properties(sajson::sajson PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${sajson_INCLUDE_DIR}
	)
endif()
