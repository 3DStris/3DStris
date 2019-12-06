# the commit's SHA1 (abbreviated to 7 characters), and whether the building workspace was dirty or not
execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=7 --dirty
  WORKING_DIRECTORY "${3dstris_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_SHA1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file("${3dstris_SOURCE_DIR}/include/3dstris/version.hpp.in"
			   "${3dstris_SOURCE_DIR}/include/3dstris/version.hpp")

set(HEADER_LIST
	"${3dstris_SOURCE_DIR}/include/3dstris/piece.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/util.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/shapes.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/board.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/version.hpp"
        "${3dstris_SOURCE_DIR}/include/3dstris/game.hpp"
        "${3dstris_SOURCE_DIR}/include/3dstris/colors.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/state.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/states/mainmenu.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/states/playing.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/gui.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/gui/button.hpp")

add_library(3dstris STATIC
  board.cpp
  piece.cpp
  game.cpp
  state.cpp
  states/mainmenu.cpp
  states/playing.cpp
  gui.cpp
  gui/button.cpp
  ${HEADER_LIST})

target_include_directories(3dstris PUBLIC ../include)

target_link_libraries(3dstris PUBLIC 3ds::ctrulib 3ds::citro3d 3ds::citro2d)

target_compile_options(3dstris PRIVATE -mword-relocations -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft)

source_group(TREE "${3dstris_SOURCE_DIR}/include" PREFIX "Header Files" FILES
             ${HEADER_LIST})
