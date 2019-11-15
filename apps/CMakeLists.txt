add_executable(3dstris-bin 3dstris.cpp)

target_compile_options(3dstris-bin PRIVATE -mword-relocations -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft)

target_link_libraries(3dstris-bin PUBLIC 3dstris)

set(NAME "3DStris")
set(DESCRIPTION "Tetris for the 3DS")
set(AUTHOR "Mat")
set(ICON_LOCATION "${3dstris_SOURCE_DIR}/resources/icon.png")

set(BANNER_LOCATION "${3dstris_SOURCE_DIR}/resources/banner.cgfx")
set(RSF_LOCATION "${3dstris_SOURCE_DIR}/resources/3dstris.rsf")
set(SOUND_LOCATION "${3dstris_SOURCE_DIR}/resources/sound.cwav")

add_3dsx_target(3dstris-bin
	${NAME} # Name
	${DESCRIPTION} # Description
	${AUTHOR} # Author(s)
	${ICON_LOCATION} # Icon
)

if (SMDHTOOL AND BANNERTOOL AND MAKEROM)
	add_cia_target(3dstris-bin
		${RSF_LOCATION} # RSF
		${BANNER_LOCATION} # Banner
		${SOUND_LOCATION} # Sound
		${NAME} # Name
		${DESCRIPTION} # Description
		${AUTHOR} # Author(s)
		${ICON_LOCATION} # Icon
	)
else()
	message(WARNING "Not building CIA; could not find required tools.")
endif()
