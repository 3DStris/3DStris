if(GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
		WORKING_DIRECTORY ${3DStris_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_SHA1
		OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

configure_file("${3DStris_SOURCE_DIR}/include/3dstris/version.hpp.in"
			   "${3DStris_SOURCE_DIR}/include/3dstris/version.hpp")

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${3DStris_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${3DStris_SOURCE_DIR}/include/3dstris/*.hpp")

add_executable(3dstris ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(3dstris PUBLIC ../include)
set(ROMFS_LOCATION "${3DStris_SOURCE_DIR}/data/romfs")
add_t3s(3dstris ${ROMFS_LOCATION}
	"${3DStris_SOURCE_DIR}/data/gfx/sprites.t3s"
	"${3DStris_SOURCE_DIR}/data/gfx/images.t3s")

target_link_libraries(3dstris PRIVATE
	3ds::ctrulib 3ds::citro3d 3ds::citro2d
	sds::sds
	sajson::sajson
	robin_hood::robin_hood
	mpack::mpack
	pcg::pcg)
target_compile_definitions(3dstris PUBLIC SAJSON_NO_STD_STRING)

source_group(TREE "${3DStris_SOURCE_DIR}/include"
			 PREFIX "Header Files"
			 FILES ${HEADER_LIST})

set(AUTHOR "Contributors to the 3DStris project")
set(ICON_LOCATION "${3DStris_SOURCE_DIR}/data/icon.png")

add_3dsx_target(3dstris
	${CMAKE_PROJECT_NAME} # Name
	${CMAKE_PROJECT_DESCRIPTION} # Description
	${AUTHOR} # Author(s)
	${ROMFS_LOCATION} # RomFS
	${ICON_LOCATION} # Icon
)

if (BUILD_CIA AND SMDHTOOL AND BANNERTOOL AND MAKEROM)
	set(PRODUCT_CODE "CTR-B-3RIS")
	set(TITLE_ID "0xED474")

	set(RSF_LOCATION "${3DStris_SOURCE_DIR}/data/cia/3dstris.rsf")
	configure_file(${RSF_LOCATION}.in
		${RSF_LOCATION})

	set(BANNER_LOCATION "${3DStris_SOURCE_DIR}/data/cia/banner.cgfx")
	set(SOUND_LOCATION "${3DStris_SOURCE_DIR}/data/cia/sound.cwav")

	add_cia_target(3dstris
		${RSF_LOCATION} # RSF
		${BANNER_LOCATION} # Banner
		${SOUND_LOCATION} # Sound
		${ROMFS_LOCATION} # RomFS
		${CMAKE_PROJECT_NAME} # Name
		${CMAKE_PROJECT_DESCRIPTION} # Description
		${AUTHOR} # Author(s)
		${ICON_LOCATION} # Icon
	)
elseif(NOT BUILD_CIA)
	message("Not building CIA; BUILD_CIA: ${BUILD_CIA}")
else()
	message(WARNING "Not building CIA; could not find required tools.")
endif()
