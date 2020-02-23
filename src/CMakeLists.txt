execute_process(COMMAND
	"${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=7 --dirty
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
	OUTPUT_VARIABLE GIT_SHA1
	ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file("${PROJECT_SOURCE_DIR}/include/3dstris/version.hpp.in"
			   "${PROJECT_SOURCE_DIR}/include/3dstris/version.hpp")

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/3dstris/*.hpp")

add_library(3dstris STATIC
	${SOURCE_LIST}
	${HEADER_LIST})

add_t3s(3dstris "${PROJECT_SOURCE_DIR}/resources/gfx/images.t3s")
add_t3s(3dstris "${PROJECT_SOURCE_DIR}/resources/gfx/sprites.t3s")

target_include_directories(3dstris PUBLIC ../include)

target_link_libraries(3dstris PUBLIC
	3ds::ctrulib 3ds::citro3d 3ds::citro2d
	sds::sds
	RapidJSON::RapidJSON
	phmap::phmap
	mpack::mpack)

target_compile_options(3dstris PRIVATE $<$<CONFIG:RELEASE>:-O3>)

source_group(TREE "${PROJECT_SOURCE_DIR}/include"
			 PREFIX "Header Files"
			 FILES ${HEADER_LIST})
