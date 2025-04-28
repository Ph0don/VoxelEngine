cmake_minimum_required(VERSION 3.28)

project(VoxelEngine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(VoxelEngine)
add_subdirectory(Libraries)

if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	# Startup Project
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT VoxelEngine)
endif()