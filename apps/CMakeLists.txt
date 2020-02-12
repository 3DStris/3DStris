add_executable(3dstris-bin 3dstris.cpp)

target_link_libraries(3dstris-bin PUBLIC 3dstris)

set(AUTHOR "3DStris Team")
set(ICON_LOCATION ${PROJECT_SOURCE_DIR}/resources/icon.png)
message(WARNING ${PROJECT_SOURCE_DIR}/romfs)
set(ROMFS_LOCATION ${PROJECT_SOURCE_DIR}/romfs)

set(PRODUCT_CODE "CTR-B-3RIS")
set(TITLE_ID "0xED474")
set(RSF_LOCATION ${PROJECT_SOURCE_DIR}/resources/3dstris.rsf)
configure_file(${RSF_LOCATION}.in
			   ${RSF_LOCATION})

set(BANNER_LOCATION ${PROJECT_SOURCE_DIR}/resources/banner.cgfx)
set(SOUND_LOCATION ${PROJECT_SOURCE_DIR}/resources/sound.cwav)

add_3dsx_target(3dstris-bin
	${CMAKE_PROJECT_NAME} # Name
	${CMAKE_PROJECT_DESCRIPTION} # Description
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

target_compile_options(3dstris-bin PRIVATE $<$<CONFIG:RELEASE>:-O3>)
