# 3.11.0 required for cxx_std_17 and FetchContent
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(Game VERSION 0.0.7 LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON)
option(BUILD_TESTS "Build test applications" OFF)
option(ACID_INSTALL_RESOURCES "Installs the Resources directory" ON)
option(ACID_LINK_RESOURCES "Passes local Resources directory into debug Confg" ON)

# Used to include Acid CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/External/Acid/CMake" CACHE STRING "Modules for CMake" FORCE)
include(AcidIncludeDirs)

# Uses git to find the current git branch and commit.
execute_process(
		COMMAND git rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GAME_GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET
		)

execute_process(
		COMMAND git log -1 --format=%h
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GAME_GIT_COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET
		)

# Acid engine engine
set(ACID_INSTALL_EXAMPLES OFF CACHE INTERNAL "")
set(BUILD_TESTS_EDITOR OFF CACHE INTERNAL "")
set(BUILD_TESTS_TUTORIAL OFF CACHE INTERNAL "")
set(BUILD_TESTS_UNITS OFF CACHE INTERNAL "")
add_subdirectory(External/Acid)

# Game sources directory
add_subdirectory(Sources)
