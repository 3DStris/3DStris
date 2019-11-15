cmake_minimum_required(VERSION 3.12...3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lib/3ds-cmake/DevkitArm3DS.cmake)

set(3dstris_VERSION_MAJOR 0)
set(3dstris_VERSION_MINOR 2)
set(3dstris_VERSION_PATCH 0)
set(3dstris_VERSION "${3dstris_VERSION_MAJOR}.${3dstris_VERSION_MINOR}.${3dstris_VERSION_PATCH}")

project(
  3dstris
  VERSION ${3dstris_VERSION}
  DESCRIPTION "Tetris for the 3DS"
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/3ds-cmake/cmake)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
endif()

include(Tools3DS)
find_package(CTRULIB REQUIRED)
find_package(CITRO3D REQUIRED)
find_package(CITRO2D REQUIRED)

add_subdirectory(src)
add_subdirectory(apps)
