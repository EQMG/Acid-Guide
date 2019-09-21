# All of these will be set as PUBLIC sources to Game
set(_temp_game_headers
		)
set(_temp_game_sources
		Main.cpp
		)

# Directory that Game resources can be found.
get_filename_component(CURRENT_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
set(GAME_RESOURCES_DIR "${CURRENT_PARENT_DIR}/Resources")

# Adds a CMake generated config file
configure_file(Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp)

# Sets all headers as PRIVATE sources for Game
# The BUILD/INSTALL interface generator expressions are for the EXPORT command
# Otherwise it wouldn't know where to look for them
foreach(_game_header IN LISTS _temp_game_headers)
	target_sources(Game PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_game_header}>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${_game_header}>
			)
endforeach()
# Sets all sources (cpp) as PRIVATE sources for Game
# An INSTALL_INTERFACE isn't needed, as cpp files aren't installed
foreach(_game_source IN LISTS _temp_game_sources)
	target_sources(Game PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_game_source}>
			)
endforeach()
