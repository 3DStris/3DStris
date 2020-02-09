add_executable(3dstris-bin 3dstris.cpp)

target_link_libraries(3dstris-bin PUBLIC 3dstris)

set(NAME "3DStris")
set(DESCRIPTION "Tetris for the 3DS")
set(AUTHOR "3DStris Team")
set(ICON_LOCATION "${3dstris_SOURCE_DIR}/resources/icon.png")
set(ROMFS_LOCATION "${3dstris_SOURCE_DIR}/romfs")

set(PRODUCT_CODE "CTR-B-3RIS")
set(TITLE_ID "0xED474")
set(RSF_LOCATION "${3dstris_SOURCE_DIR}/resources/3dstris.rsf")
configure_file("${3dstris_SOURCE_DIR}/resources/3dstris.rsf.in"
			   "${RSF_LOCATION}")

set(BANNER_LOCATION "${3dstris_SOURCE_DIR}/resources/banner.cgfx")
set(SOUND_LOCATION "${3dstris_SOURCE_DIR}/resources/sound.cwav")

add_3dsx_target(3dstris-bin
	${NAME} # Name
	${DESCRIPTION} # Description
	${AUTHOR} # Author(s)
	${ROMFS_LOCATION} # RomFS
	${ICON_LOCATION} # Icon
)

if (BUILD_CIA AND SMDHTOOL AND BANNERTOOL AND MAKEROM)
	add_cia_target(3dstris-bin
		${RSF_LOCATION} # RSF
		${BANNER_LOCATION} # Banner
		${SOUND_LOCATION} # Sound
		${ROMFS_LOCATION} # RomFS
		${NAME} # Name
		${DESCRIPTION} # Description
		${AUTHOR} # Author(s)
		${ICON_LOCATION} # Icon
	)
elseif(NOT BUILD_CIA)
	message("Not building CIA; BUILD_CIA: ${BUILD_CIA}")
else()
	message(WARNING "Not building CIA; could not find required tools.")
endif()

target_compile_options(3dstris-bin PRIVATE $<$<CONFIG:RELEASE>:-O3>)
