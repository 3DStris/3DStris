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
	games.hpp
	state.hpp
	states/mainmenu.hpp
	states/ingame.hpp
	states/playing.hpp
	states/sprint.hpp
	states/paused.hpp
	states/results.hpp
	states/sprintresults.hpp
	states/sprinttimes.hpp
	states/configscreen.hpp
	states/loadfailed.hpp
	states/languages.hpp
	util/text.hpp
	util/l10n.hpp
	gui.hpp
	gui/widget.hpp
	gui/button.hpp
	gui/togglebutton.hpp
	gui/languagebutton.hpp
	gui/u32inputfield.hpp
	gui/panel.hpp
	wallkicks.hpp)

add_library(3dstris STATIC
	board.cpp
	piece.cpp
	game.cpp
	colors.cpp
	config.cpp
	games.cpp
	state.cpp
	states/mainmenu.cpp
	states/modeselect.cpp
	states/ingame.cpp
	states/playing.cpp
	states/sprint.cpp
	states/paused.cpp
	states/results.cpp
	states/sprintresults.cpp
	states/sprinttimes.cpp
	states/configscreen.cpp
	states/loadfailed.cpp
	states/languages.cpp
	util/text.cpp
	util/l10n.cpp
	gui.cpp
	gui/widget.cpp
	gui/button.cpp
	gui/togglebutton.cpp
	gui/languagebutton.cpp
	gui/u32inputfield.cpp
	gui/panel.cpp
	${HEADER_LIST})

add_t3s(3dstris "${3dstris_SOURCE_DIR}/resources/gfx/images.t3s")
add_t3s(3dstris "${3dstris_SOURCE_DIR}/resources/gfx/sprites.t3s")

target_include_directories(3dstris PUBLIC ../include)

target_link_libraries(3dstris PUBLIC
	3ds::ctrulib 3ds::citro3d 3ds::citro2d
	sds
	RapidJSON::RapidJSON
	phmap::phmap)

target_compile_options(3dstris PRIVATE $<$<CONFIG:RELEASE>:-O3>)

source_group(TREE "${3dstris_SOURCE_DIR}/include"
			 PREFIX "Header Files"
			 FILES ${HEADER_LIST})
