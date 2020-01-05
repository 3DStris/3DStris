# the commit's SHA1 (abbreviated to 7 characters), and whether the building workspace was dirty or not
execute_process(COMMAND
	"${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=7 --dirty
	WORKING_DIRECTORY "${3dstris_SOURCE_DIR}"
	OUTPUT_VARIABLE GIT_SHA1
	ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file("${3dstris_SOURCE_DIR}/include/3dstris/version.hpp.in"
			   "${3dstris_SOURCE_DIR}/include/3dstris/version.hpp")

macro(set_header_list)
	foreach(header_file IN ITEMS ${ARGN})
		list(APPEND HEADER_LIST "${3dstris_SOURCE_DIR}/include/3dstris/${header_file}")
	endforeach()
endmacro()

set_header_list(
	piece.hpp
	util.hpp
	shapes.hpp
	board.hpp
	version.hpp
	game.hpp
	colors.hpp
	config.hpp
	state.hpp
	states/mainmenu.hpp
	states/playing.hpp
	states/paused.hpp
	states/configscreen.hpp
	states/configfailed.hpp
	util/text.hpp
	gui.hpp
	gui/widget.hpp
	gui/button.hpp
	gui/slider.hpp
	wallkicks.hpp)

add_library(3dstris STATIC
	board.cpp
	piece.cpp
	game.cpp
	config.cpp
	state.cpp
	states/mainmenu.cpp
	states/playing.cpp
	states/paused.cpp
	states/configscreen.cpp
	states/configfailed.cpp
	util/text.cpp
	gui.cpp
	gui/widget.cpp
	gui/slider.cpp
	gui/button.cpp
	${HEADER_LIST})

add_t3s(3dstris "${3dstris_SOURCE_DIR}/resources/gfx/sprites.t3s")

target_include_directories(3dstris PUBLIC ../include)

target_link_libraries(3dstris PUBLIC 3ds::ctrulib 3ds::citro3d 3ds::citro2d nlohmann_json::nlohmann_json sds)

target_compile_options(3dstris PRIVATE -mword-relocations -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -std=gnu++11)

source_group(TREE "${3dstris_SOURCE_DIR}/include"
			 PREFIX "Header Files"
			 FILES ${HEADER_LIST})
