set(RapidJSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include/rapidjson)

mark_as_advanced(RapidJSON_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RapidJSON
	REQUIRED_VARS RapidJSON_INCLUDE_DIR
	VERSION_VAR RapidJSON_VERSION
)

if(RapidJSON_FOUND)
	get_filename_component(RapidJSON_INCLUDE_DIRS ${RapidJSON_INCLUDE_DIR} DIRECTORY)
endif()

if(RapidJSON_FOUND AND NOT TARGET RapidJSON::RapidJSON)
	add_library(RapidJSON::RapidJSON INTERFACE IMPORTED)
	set_target_properties(RapidJSON::RapidJSON PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${RapidJSON_INCLUDE_DIRS}
	)
endif()
