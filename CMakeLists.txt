cmake_minimum_required(VERSION 3.12...3.15)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/external/3ds-cmake/DevkitArm3DS.cmake")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(3DStris_VERSION_MAJOR 1)
set(3DStris_VERSION_MINOR 6)
set(3DStris_VERSION_PATCH 4)
set(3DStris_VERSION ${3DStris_VERSION_MAJOR}.${3DStris_VERSION_MINOR}.${3DStris_VERSION_PATCH})

project(
	3DStris
	VERSION ${3DStris_VERSION}
	DESCRIPTION "A Tetris clone for the 3DS"
	LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${3DStris_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${3DStris_SOURCE_DIR}/external/3ds-cmake/cmake")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	string(APPEND CMAKE_C_FLAGS " ${DKA_SUGGESTED_C_FLAGS} -Wall -Wextra")
	string(APPEND CMAKE_CXX_FLAGS " ${DKA_SUGGESTED_CXX_FLAGS} -Wno-psabi -Wall -Wextra")

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
endif()

macro(_3dstris_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
	option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
	if(DEFINED ENV{${OPTION_NAME}})
		# Allow setting the option through an environment variable
		set(${OPTION_NAME} $ENV{${OPTION_NAME}})
	endif()
	message("${OPTION_NAME} (${OPTION_TEXT}): ${${OPTION_NAME}}")
endmacro()

message("3DStris CMake options")
message("================================================")
_3dstris_option(BUILD_CIA "Whether or not to build a CIA" ON)
message("================================================")

find_package(Git)

include(Tools3DS)
find_package(ctrulib REQUIRED)
find_package(Citro3D REQUIRED)
find_package(Citro2D REQUIRED)

find_package(RapidJSON REQUIRED)
find_package(phmap REQUIRED)
find_package(pcg REQUIRED)
add_subdirectory(external)

add_subdirectory(src)
