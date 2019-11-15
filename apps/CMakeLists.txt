add_executable(3dstris-main 3dstris.cpp)

target_compile_options(3dstris-main PRIVATE -mword-relocations -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft)

target_link_libraries(3dstris-main PUBLIC 3dstris)

set(NAME "3DSTris")
set(DESCRIPTION "Tetris for the 3DS")
set(AUTHOR "Mat")
set(ICON_LOCATION "${3dstris_SOURCE_DIR}/resources/icon.png")

set(BANNER_LOCATION "${3dstris_SOURCE_DIR}/resources/banner.png")
set(RSF_LOCATION "${3dstris_SOURCE_DIR}/resources/3dstris.rsf")
set(SOUND_LOCATION "${3dstris_SOURCE_DIR}/resources/sound.cwav")


add_3dsx_target(3dstris-main
	${NAME} # Name
	${DESCRIPTION} # Description
	${AUTHOR} # Author(s)
	${ICON_LOCATION} # Icon
)

add_cia_target(3dstris-main
	${RSF_LOCATION} # RSF
	${BANNER_LOCATION} # Banner
	${SOUND_LOCATION} # Sound
	${NAME} # Name
	${DESCRIPTION} # Description
	${AUTHOR} # Author(s)
	${ICON_LOCATION} # Icon
)
