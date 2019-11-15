configure_file("${3dstris_SOURCE_DIR}/include/3dstris/version.hpp.in"
			   "${3dstris_SOURCE_DIR}/include/3dstris/version.hpp")

set(HEADER_LIST
	"${3dstris_SOURCE_DIR}/include/3dstris/piece.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/util.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/shapes.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/board.hpp"
	"${3dstris_SOURCE_DIR}/include/3dstris/version.hpp")

add_library(3dstris STATIC
  board.cpp
  piece.cpp
  ${HEADER_LIST})

target_include_directories(3dstris PUBLIC ../include)

target_link_libraries(3dstris PUBLIC 3ds::ctrulib 3ds::citro3d 3ds::citro2d)

target_compile_options(3dstris PRIVATE -mword-relocations -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft)

source_group(TREE "${3dstris_SOURCE_DIR}/include" PREFIX "Header Files" FILES
             ${HEADER_LIST})
