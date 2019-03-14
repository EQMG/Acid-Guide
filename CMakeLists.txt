# 3.11.0 required for cxx_std_17 and FetchContent
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(Game VERSION 0.0.4 LANGUAGES C CXX)

# Sets the install directories defined by GNU
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Use ccache if it is installed, will cach previous compilations
find_program(CCACHE_FOUND "ccache")
if(CCACHE_FOUND)
	message(STATUS "Using ccache for building.")
	set_property(GLOBAL PROPERTY LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

# Allows usage of configure time content
include(FetchContent)

FetchContent_Declare(acid
		GIT_REPOSITORY https://github.com/Equilibrium-Games/Acid.git
		GIT_TAG master
		)
FetchContent_GetProperties(acid)
if(NOT acid_POPULATED)
	foreach(_acid_option "BUILD_TESTS" "ACID_INSTALL_EXAMPLES" "ACID_INSTALL_RESOURCES")
		set(${_acid_option} OFF CACHE INTERNAL "")
	endforeach()
	FetchContent_Populate(acid)
	add_subdirectory(${acid_SOURCE_DIR} ${acid_BINARY_DIR})
endif()
set(ACID_INCLUDE_DIR "${acid_SOURCE_DIR}/Sources")

# Sources
add_subdirectory(Sources)
